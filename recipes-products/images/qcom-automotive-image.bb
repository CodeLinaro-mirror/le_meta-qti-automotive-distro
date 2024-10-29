include recipes-products/images/machine-image.bb

SUMMARY = "core image of automotive"
USERADD_PACKAGES = "${PN}"
LICENSE = "BSD-3-Clause-Clear"

# CORE_IMAGE_BASE_INSTALL
# IMAGE_INSTALL += " \
#     packagegroup-qcom-automotive-core-boot \
# "

IMAGE_INSTALL += " \
    packagegroup-qti-core-minimal \
    packagegroup-qti-umd \
"

IMAGE_INSTALL:remove += " \
    packagegroup-qti-umd \
" 
