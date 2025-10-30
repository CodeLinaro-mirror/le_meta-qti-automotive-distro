# Support systemd-user-session
DISTRO_FEATURES:append = " pam"

# Disable pulseaudio
DISTRO_FEATURES_BACKFILL_CONSIDERED:append:gen5 = " pulseaudio"

# Display
DISTRO_FEATURES:append = " wayland"

DISTRO_FEATURES:append = " opengl"

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
DISTRO_FEATURES:remove:gen5 = "wifi"


# SELinux
DISTRO_FEATURES:append:gen5 = " selinux"
DISTRO_FEATURES_NATIVE:append:gen5 = " selinux"

# Preferred refpolicy
PREFERRED_PROVIDER_virtual/refpolicy:gen5 = "selinux-policy"
DEFAULT_ENFORCING:gen5 = "enforcing"

PREFERRED_PROVIDER_virtual/refpolicy:sa8775 = "selinux-policy"
DEFAULT_ENFORCING:sa8775 = "permissive"

PREFERRED_PROVIDER_virtual/refpolicy:sa7255 = "selinux-policy"
DEFAULT_ENFORCING:sa7255 = "permissive"

DISTRO_FEATURES:remove:pn-core-image-minimal = "selinux"

# Disable QCLinux Yocto Unused Distro
DISTRO_FEATURES:remove = "x11"

# Virtiofsd
DISTRO_FEATURES:append = " seccomp"

# Video
DISTRO_FEATURES:append:gen5 = " qti-gstdeinterlace"
