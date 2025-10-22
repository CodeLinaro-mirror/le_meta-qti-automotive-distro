# Eliminate gpl3 gdbm dependency
PACKAGECONFIG:remove:pn-perl = "gdbm"
PACKAGECONFIG:remove:pn-python3 = "gdbm"

# Eliminate gpl3 kbd-keymaps-pine dependency
RRECOMMENDS:${PN}-keymaps:remove:pn-kbd = "${PN}-keymaps-pine"

# Eliminate gpl3 readline dependency
PACKAGECONFIG:remove:pn-nftables = "readline"

IMAGE_INSTALL:remove:pn-machine-image = "rt-tests"
IMAGE_INSTALL:remove:pn-early-ramdisk-image = "rt-tests"

# Eliminate gpl3 bash dependency
RDEPENDS:${PN}:remove:pn-alsa-utils = "alsa-utils-scripts"

# Eliminate gpl3 dependency duo to selinux
RDEPENDS:${PN}:remove:pn-packagegroup-selinux-minimal = "coreutils"
RDEPENDS:${PN}:remove:pn-selinux-init = "coreutils"
RDEPENDS:${PN}:remove:pn-selinux-labeldev = "coreutils"
RDEPENDS:${PN}-sepolicy:remove:pn-selinux-python = "binutils"
RDEPENDS:${PN}-fixfiles:remove:pn-policycoreutils = "grep findutils"


EXTRA_IMAGE_FEATURES:remove:pn-machine-image = "package-management"
