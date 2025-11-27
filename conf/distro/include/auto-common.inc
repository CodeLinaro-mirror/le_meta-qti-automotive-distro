require conf/distro/include/security_flags.inc

require conf/distro/include/distro_features.inc

require conf/distro/include/non-gplv3-license.inc

require conf/distro/include/base.inc

DISTRO_NAME = "automotive"
DISTROOVERRIDES =. "automotive:"
# Support SDP
ID_LIKE = "automotive"

PRODUCT ?= "${MACHINE}" 
DEPLOY_NAME_BASE = "${PRODUCT}-automotive"
IMAGE_NAME = "${IMAGE_BASENAME}-${PRODUCT}${IMAGE_VERSION_SUFFIX}"
IMAGE_LINK_NAME = "${IMAGE_BASENAME}-${PRODUCT}"

PERSIST_IMAGE_ROOTFS_SIZE ?= "128M"

VIRTUAL-RUNTIME_dev_manager = "udev"
VIRTUAL-RUNTIME_init_manager = "systemd"

IMAGE_FEATURES:append = " read-only-rootfs"

LICENSE_FLAGS_ACCEPTED += "commercial_gstreamer1.0-libav commercial_gstreamer1.0-omx"
LICENSE_FLAGS_ACCEPTED += "commercial_gstreamer1.0-plugins-ugly commercial_opencore-amr"
LICENSE_FLAGS_ACCEPTED += "commercial_ffmpeg"

ERROR_QA:remove:sa8775 = "patch-fuzz"

# In Scarthgap, there is currently not "ignore .debug files", So skip this QA check to avoid too many build warnings.
WARN_QA:remove = "buildpaths"

# include ${DISTRO_INC_FILES}

# Sizes for EXT4 (in bytes)
SYSTEM_SIZE_EXT4 ?= "100000000"
SYSTEMRW_SIZE_EXT4 ?= "8388608"
USERDATA_SIZE_EXT4 ?= "2000000000"
CACHE_SIZE_EXT4 ?= "80000000"
PERSIST_IMAGE_ROOTFS_SIZE ?= "128M"

BB_DANGLINGAPPENDS_WARNONLY = "yes"

#Align with poky/meta-poky/conf/distro/poky.conf
OE_VERSION ?= "4.0.7"
