SUMMARY = "LED Driver"

DESCRIPTION = "${SUMMARY}"

# License type (closed-source).
LICENSE = "closed"

# Inherit functionality from the module class for kernel modules.
inherit module

# Source URI for fetching the code from a local Git repository.
SRC_URI = "git:///home/ahmedsami/SmartHome-IoT/driver;protocol=file;branch=kirkstone"

# Use the latest commit from the specified branch.
SRCREV = "${AUTOREV}"

# Directory where the source code will be located during the build.
S = "${WORKDIR}/git"

# Declare that this recipe provides a kernel module.
RPROVIDES:${PN} += "kernel-module-gpiodriver"
