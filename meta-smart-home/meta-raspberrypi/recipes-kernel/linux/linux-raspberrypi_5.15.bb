LINUX_VERSION ?= "5.15.92"
LINUX_RPI_BRANCH ?= "rpi-5.15.y"
LINUX_RPI_KMETA_BRANCH ?= "yocto-5.15"

SRCREV_machine = "14b35093ca68bf2c81bbc90aace5007142b40b40"
SRCREV_meta = "509f4b9d68337f103633d48b621c1c9aa0dc975d"

KMETA = "kernel-meta"

SRC_URI = " \
    git://github.com/raspberrypi/linux.git;name=machine;branch=${LINUX_RPI_BRANCH};protocol=https \
    git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=${LINUX_RPI_KMETA_BRANCH};destsuffix=${KMETA} \
    file://0001-wifi-cfg80211-Add-my-certificate.patch \
    file://0002-wifi-cfg80211-fix-certs-build-to-not-depend-on-file-.patch \
    file://powersave.cfg \
    file://android-drivers.cfg \
    "

require linux-raspberrypi.inc

KERNEL_DTC_FLAGS += "-@ -H epapr"
