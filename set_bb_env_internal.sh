# Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause-Clear

# set_bb_env_internal.sh
# Call set_bb_env_internal.sh in meta-qti-internal layer.
# Set ROS layers

# The SHELL variable also needs to be set to /bin/bash otherwise the build
# will fail, use chsh to change it to bash.
if [[ ! $SHELL =~ bash ]]
then
    echo ""
    echo "### ERROR: Please Change your shell to bash using chsh. ### "
    echo ""
    echo "### Make sure that the SHELL variable points to /bin/bash ### "
    echo ""
    return 1
fi

umask 022

# This script
THIS_SCRIPT=$(readlink -f ${BASH_SOURCE[0]})
# Find where the global conf directory is...
scriptdir="$(dirname "${THIS_SCRIPT}")"
# Find where the WS is...
SRC_TREE=$(readlink -f $scriptdir/../..)

source ${SRC_TREE}/setup-environment

# Automotive yocto conf update

cat >> ${BUILDDIR}/conf/auto.conf <<EOF

#----------------------------------------
# Include automotive yocto ENV
#----------------------------------------

#Disable multiconfig build for automotive
INHERIT += "qfile"
BBMULTICONFIG:remove = "qcom-guestvm"
# DL_DIR = "${DL_DIR}"
BB_GENERATE_MIRROR_TARBALLS="1"
PATH_TO_REPO ?= "file://"
AUTOSOURCES = "${SRC_TREE}"
# AUTOSOURCES = "${SRC_TREE}/sources/automotive"

# Specify the path of the sectools tool and the security file required for lemans signature
SECTOOLS_V1_DIR ??= "/pkg/sectools/int/latest"
SECTOOLS_V2_DIR ??= "/pkg/sectools/v2/1.21/Linux"
SECTOOLS_SECURITY_PROFILE ??= "${SRC_TREE}/security/securemsm/security_profiles/lemans_tz_security_profile.xml"

INHERIT:remove = "rm_work"
VARIANT = "${QVARIANT}"
SRC_DIR_ROOT = "${SRC_TREE}"
export KDIR := "${SRC_TREE}/kernel/kernel_platform/kernel"
PATH_TO_REPO := "git://${SRC_TREE}"
PROTO = "file"
PATH_TO_KERNEL := "git://${SRC_TREE}/sources"

#Override by automotive yocto
DISTRO_VERSION = "\${BUILDNAME}"

# BB_BASEHASH_IGNORE_VARS Tells bitbake to ignore variables
# The SRC_DIR_ROOT variable is added through build/conf/bblayers.conf
BB_BASEHASH_IGNORE_VARS:append = " SRC_TREE KDIR WORKSPACE AUTOSOURCES PATH_TO_KERNEL BSPDIR BUILDNAME SRC_DIR_ROOT PATH_TO_REPO QTI_METAPATH_BASE QTI_METAPATH_BASE_PROP QTI_METAPATH_DISTRO \ "

# Show VARIANT in pre-build configuration output
BUILDCFG_VARS += "VARIANT MACHINE_FEATURES"

# Enable hash equivalency
BB_SIGNATURE_HANDLER = "OEEquivHash"
BB_HASHSERVE = "auto"

PACKAGE_DEBUG_SPLIT_STYLE = ".debug"

EOF


# Add automotive layers with CSE internal layers
if [ -e "${SRC_TREE}/layers/meta-qti-distro/conf/bblayers.conf" ]; then
    sed -i '/meta-qcom\|meta-rust\|meta-security/d' ${SRC_TREE}/layers/meta-qti-distro/conf/bblayers.conf
    cat ${SRC_TREE}/layers/meta-qti-distro/conf/bblayers.conf > ${BUILDDIR}/conf/bblayers.conf
    cat >> ${BUILDDIR}/conf/bblayers.conf <<EOF
BSPLAYERS += "\\
  ${SRC_TREE}/layers/meta-qti-distro \\
  ${SRC_TREE}/layers/meta-qti-bsp \\
  ${SRC_TREE}/layers/meta-qti-bsp-prop \\
  ${SRC_TREE}/layers/meta-qti-internal \\
  ${SRC_TREE}/layers/meta-qcom \\
"
EOF
fi

#HY11 build don't need these layers
if [ -d "${SRC_TREE}/layers/meta-qti-automotive-internal" ]; then
cat >> ${BUILDDIR}/conf/bblayers.conf <<EOF
EXTRALAYERS += "\\
  ${SRC_TREE}/layers/meta-qti-automotive-internal \\
  ${SRC_TREE}/layers/meta-qt5 \\
"
EOF
fi

sed -i -e '/^WORKSPACE/d' -e 's/WORKSPACE/SRC_TREE/g' ${BUILDDIR}/conf/bblayers.conf
cat >> ${BUILDDIR}/conf/bblayers.conf <<EOF
EXTRALAYERS += "\\
  ${SRC_TREE}/layers/meta-qti-automotive-prop \\
  ${SRC_TREE}/layers/meta-qti-automotive-distro \\
  ${SRC_TREE}/layers/meta-qti-automotive \\
  ${SRC_TREE}/layers/meta-qti-realtime \\
  ${SRC_TREE}/layers/meta-qti-auto-kernel \\
  ${SRC_TREE}/layers/meta-clang \\
"

SRC_TREE = "${SRC_TREE}"
EOF

if [ -f ${SRC_TREE}/layers/meta-qcom-hwe/classes/qprebuilt.bbclass ]; then
  #Conflict and remove qprebuilt.bbclass from meta-qcom-hwe
  echo "Remove ${SRC_TREE}/layers/meta-qcom-hwe/classes/qprebuilt.bbclass"
  rm -f ${SRC_TREE}/layers/meta-qcom-hwe/classes/qprebuilt.bbclass
fi

cat >> ${BUILDDIR}/conf/local.conf <<EOF
USER_CLASSES ?= "buildname"
BUILDNAME = "\${@get_tag('\${SRC_DIR_ROOT}', d)}"

# Let pkgs install files that other pkgs want to install for the recovery images.
OPKG_ARGS:append = " --force-overwrite"
EOF
