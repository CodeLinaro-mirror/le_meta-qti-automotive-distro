# Support systemd-user-session
DISTRO_FEATURES:append = " pam"



# Display
DISTRO_FEATURES:append = " wayland"


# Use synergy, disable bluez
DISTRO_FEATURES_BACKFILL_CONSIDERED += "bluez5 bluetooth"

#Enable persist-image
DISTRO_FEATURES:append = " persist-image "

DISTRO_FEATURES:append = " qti-early-eth"
#DISTRO_FEATURES:append = " early_init"
#DISTRO_FEATURES:append = " early_userspace"


DISTRO_FEATURES:append = " hibernation"

# Use systemd init manager.
DISTRO_FEATURES:append = " systemd ${@bb.utils.contains('LAYERSERIES_CORENAMES', 'scarthgap', 'usrmerge', '', d)}"
DISTRO_FEATURES_BACKFILL_CONSIDERED += "sysvinit"

DISTRO_FEATURES:append = " vulkan"

# WLAN
DISTRO_FEATURES:append = " qti-wlan wifi"
DISTRO_FEATURES:remove:sa8797 = "wifi"


# SELinux
# DISTRO_FEATURES:append:sa8797 = " selinux"
# DISTRO_FEATURES_NATIVE:append:sa8797 = " selinux"
#TODO enable on sa8797

# Preferred refpolicy
# PREFERRED_PROVIDER_virtual/refpolicy:sa8797 = "selinux-policy"
# DEFAULT_ENFORCING:sa8797 = "enforcing"

# Disable QCLinux Yocto Unused Distro
DISTRO_FEATURES:remove = "x11"

# Virtiofsd
DISTRO_FEATURES:append = " seccomp"

# Video
DISTRO_FEATURES:append:sa8797 = " qti-gstdeinterlace"
