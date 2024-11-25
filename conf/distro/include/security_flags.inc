# Pull in the default security flags
require ${COREBASE}/meta/conf/distro/include/security_flags.inc

# Modify the primary security flag definitions of yocto
# _FORTIFY_SOURCE requires -O1 or higher, otherwise results in a compiler warning.
SECURITY_PIE_CFLAGS = "-fstack-protector-strong -pie -fPIE -D_FORTIFY_SOURCE=2 -Wa,--noexecstack ${SECURITY_STRINGFORMAT}"

# For usage by packages which needs position independent code that can be linked into shared libraires.
SECURITY_PIC_CFLAGS = "-fstack-protector-strong -fPIC -D_FORTIFY_SOURCE=2 -Wa,--noexecstack ${SECURITY_STRINGFORMAT}"

SECURITY_CFLAGS = "${SECURITY_PIE_CFLAGS}"
SECURITY_LDFLAGS = "-Wl,-z,relro,-z,now,-z,noexecstack"

# edk2
SECURITY_CFLAGS:pn-edk2 = "-pie -fpie -Wa,--noexecstack"

#
### PACKAGES to use -fPIC in security flags instead of -fPIE
#
# GPS OSS packages
SECURITY_CFLAGS:pn-gps-utils = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-loc-hal = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-loc-core = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-loc-api-v02 = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-loc-ds = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-loc-net-iface = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-location-api = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-loc-base-util = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-loc-mq-client = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-izat-core = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-lowi-client = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-lbs-core = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-drplugin-client = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-drplugin = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-ulp2 = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-location-flp = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-location-service = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-loc-glue = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-location-batching = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-location-geofence = "${SECURITY_PIC_CFLAGS}"

# General purpose OSS packages
SECURITY_CFLAGS:pn-gtest = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-go-runtime = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-binder  = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-libcutils  = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-liblog  = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-av-frameworks  = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-libbase = "${SECURITY_PIC_CFLAGS}"
# libutils needs -fPIC
SECURITY_CFLAGS_pn_libutils = "${SECURITY_PIC_CFLAGS}"

# BT OSS packages
SECURITY_CFLAGS:pn-event-observer = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-data-items = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-bt-property = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-bt-app = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-libbt-vendor = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-fluoride = "${SECURITY_PIC_CFLAGS}"

# MM packages
SECURITY_CFLAGS:pn-display-hal = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-media = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-lib32-media = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-qmmf-sdk = "${SECURITY_PIC_CFLAGS}"
SECURITY_CFLAGS:pn-lib32-qmmf-sdk = "${SECURITY_PIC_CFLAGS}"

#
### PACKAGES which can't compile with _FORTIFY_SOURCE
#
SECURITY_CFLAGS:remove:pn-ebtables = "-D_FORTIFY_SOURCE=2"

# PACKAGES which will runtime sigabrt with _FORTIFY_SOURCE
SECURITY_CFLAGS:remove:pn-tar = "-D_FORTIFY_SOURCE=2"

#
### PACKAGES which can't compile with security format strings check
#
SECURITY_CFLAGS:remove:pn-audiohal = "${SECURITY_STRINGFORMAT}"
SECURITY_CFLAGS:remove:pn-setools = "${SECURITY_STRINGFORMAT}"

SECURITY_CFLAGS:pn-tbb = "${SECURITY_PIC_CFLAGS}"

# OSS freetype can't compile with -pie -fPIE
SECURITY_CFLAGS:pn-freetype = "${SECURITY_PIC_CFLAGS}"

# Enable some warning options to error.
EXT_COMPILE_OPTIONS = "\
    -Wall \
    -Wextra \
    -Werror=format \
    -Werror=format-overflow=2 \
    -Werror=format-truncation=2 \
    -Werror=null-dereference \
    -Werror=shift-overflow=2 \
    -Werror=logical-op \
    -Werror=format-signedness \
    -Werror=switch-default \
    -Werror=array-bounds \
    -Werror=char-subscripts \
    -Werror=missing-braces \
    -Werror=nonnull \
    -Wnonnull-compare \
    -Werror=parentheses \
    -Werror=return-type \
    -Werror=sequence-point \
    -Werror=sign-compare \
    -Werror=switch \
    -Werror=uninitialized \
    -Werror=clobbered \
    -Werror=empty-body \
    -Werror=missing-field-initializers \
    -Werror=type-limits \
    -Werror=unused-parameter \
    -Werror=conversion \
    -Werror=sign-conversion \
    -Werror=format-security \
    -Werror=implicit-fallthrough \
    -Werror=trampolines \
 "

# Platform packages
TARGET_CFLAGS:remove = "${@bb.utils.contains('SECURITY_CFLAGS', '-Werror=uninitialized', '-Wno-error=maybe-uninitialized', '', d)}"

SECURITY_CFLAGS:append:pn-liblog = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-liblog = " -Werror=format-truncation=2"

SECURITY_CFLAGS:append:pn-libcutils = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-libcutils = " -Werror=conversion \
                                        -Werror=sign-conversion \
                                        -Werror=format-truncation=2 \
                                        -Werror=format"

SECURITY_CFLAGS:append:pn-libutils = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-libutils = " -Werror=conversion \
                                       -Werror=sign-conversion"

SECURITY_CFLAGS:append:pn-libsparse = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-libsparse = " -Werror=conversion \
                                        -Werror=sign-conversion"

SECURITY_CFLAGS:append:pn-libion = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-libion = " -Werror=conversion \
                                     -Werror=sign-conversion \
                                     -Werror=null-dereference \
                                     -Werror=shift-overflow=2"

SECURITY_CFLAGS:append:pn-safe-iop = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-safe-iop = " -Werror=shift-overflow=2"

SECURITY_CFLAGS:append:pn-libmincrypt = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-libmincrypt = " -Werror=conversion \
                                          -Werror=sign-conversion"

SECURITY_CFLAGS:append:pn-binder = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-binder = " -Werror=conversion \
                                     -Werror=sign-conversion \
                                     -Werror=format-overflow=2"

SECURITY_CFLAGS:append:pn-libdmabufheap = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-libdmabufheap = " -Werror=conversion \
                                            -Werror=sign-conversion"

SECURITY_CFLAGS:append:pn-ext4-utils = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-ext4-utils = " -Werror=conversion \
                                         -Werror=sign-conversion \
                                         -Werror=clobbered"

SECURITY_CFLAGS:append:pn-libbase = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-libbase = " -Werror=conversion \
                                      -Werror=sign-conversion"

SECURITY_CFLAGS:append:pn-system-core = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-system-core = " -Werror=conversion \
                                          -Werror=sign-conversion \
                                          -Werror=missing-field-initializers"

SECURITY_CFLAGS:append:pn-libhardware = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-libhardware = " -Werror=conversion \
                                          -Werror=sign-conversion"

SECURITY_CFLAGS:append:pn-ss-services = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-ss-services = " -Werror=conversion \
                                          -Werror=sign-conversion"

SECURITY_CFLAGS:append:pn-qmi-framework = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-qmi-framework = " -Werror=conversion \
                                            -Werror=sign-conversion \
                                            -Werror=missing-field-initializers \
                                            -Werror=clobbered \"


SECURITY_CFLAGS:append:pn-time-genoff = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-time-genoff = " -Werror=conversion \
                                          -Werror=sign-conversion"

SECURITY_CFLAGS:append:pn-time-services = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-time-services = " -Werror=conversion \
                                            -Werror=sign-conversion \
                                            -Werror=missing-field-initializers \
                                            -Werror=format-truncation=2 \"

# Video packages
SECURITY_CFLAGS:append:quin-gvm-gen4-2:pn-codec2-app = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:quin-gvm-gen4-2:pn-codec2-app = " -Werror=conversion \
                                                         -Werror=sign-conversion \
                                                         -Werror=missing-field-initializers"

# avb-utils
SECURITY_CFLAGS:append:pn-avb-utils = " ${EXT_COMPILE_OPTIONS}"
SECURITY_CFLAGS:remove:pn-avb-utils = " -Werror=conversion \
                                        -Werror=sign-conversion"
# Add other packages here...
