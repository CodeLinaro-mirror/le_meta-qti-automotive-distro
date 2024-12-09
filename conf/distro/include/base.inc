#############################################################################
#@COMMENT: This distribution configuration defines an OE Linux based
#@COMMENT: distribution. The matching buildable image target (machine-image)
#@COMMENT: basically consists of: libc, busybox, udev, sysv init, and a few
#@COMMENT: init scripts for running up the system on qti chipsets.
#############################################################################
BASEDISTRO ??= ""

# Add BASEDISTRO to overrides
DISTROOVERRIDES =. "${@['', '${BASEDISTRO}:']['${BASEDISTRO}' != '']}"

# DISTRO FEATURE SELECTION
MICRO_GOLD ?= "ld-is-gold"

USE_DEVFS = "0"

# Use Debian naming scheme for library (.so) files
INHERIT += "recipe_sanity"

# TOOLCHAIN
PREFERRED_VERSION_autoconf ?= "2.68"
ARM_INSTRUCTION_SET       ?= "arm"

##################################################################
# Optimization flags.
##################################################################
COMMON_OPTIMIZATION = " \
  -Wa,--noexecstack -ftree-vectorize -finline-functions \
  "

COMMON_OPTIMIZATION:class-target:toolchain-gcc = " \
  -fexpensive-optimizations -frename-registers -finline-limit=64 \
  -Wno-error=maybe-uninitialized -Wno-error=unused-result \
  "

FULL_OPTIMIZATION         = "-O2 -fomit-frame-pointer ${COMMON_OPTIMIZATION} "
# Enable debug option as default for variant-debug distro build
FULL_OPTIMIZATION:append = " ${@bb.utils.contains('VARIANT', 'debug', '-g', '', d)}"
DEBUG_OPTIMIZATION:append = " ${COMMON_OPTIMIZATION} "

# NLS
USE_NLS = "no"
USE_NLS_glib-2.0 = "yes"
USE_NLS_glib-2.0-native = "yes"
USE_NLS_gcc-cross = "no"

# Disable GIO module cache creation
GIO_MODULE_PACKAGES=""

# Disable binary locale generation
ENABLE_BINARY_LOCALE_GENERATION = "0"

#Allow library symlinks to exist alongside soname files
PACKAGE_SNAP_LIB_SYMLINKS = "0"

# Don't install ldconfig and associated gubbins
COMMERCIAL_LICENSE_DEPENDEES = ""

PREFERRED_VERSION_readline ?= "5.2"

PRODUCT ??= "base"

# Retain existing directory structure for msm or mdm distro images.
# Append variants like '-perf', '-user' etc to deploy dir.
DEPLOY_NAME_BASE = "${MACHINE}${@bb.utils.contains_any('DISTRO', 'msm mdm', '', '-' + d.getVar('DISTRO'), d)}"
DEPLOY_NAME = "${DEPLOY_NAME_BASE}${@['-' + d.getVar('VARIANT', True), ''][d.getVar('VARIANT', True) == ('' or 'debug')]}"
DEPLOY_DIR_IMAGE = "${DEPLOY_DIR}/images/${DEPLOY_NAME}"

# Static Users for QTI
USERADDEXTENSION ?= "useradd-staticids"
USERADD_UID_TABLES:prepend = "files/qti_passwd "
USERADD_GID_TABLES:prepend = "files/qti_group "
