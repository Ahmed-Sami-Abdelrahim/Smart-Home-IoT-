# Config-startup
SUMMARY = ""

# License type (CLOSED indicates proprietary software).
LICENSE = "CLOSED"

# Source URI for the init script file.
SRC_URI = "file://configstartup-sv"

# Source directory during the build process.
S = "${WORKDIR}"

# Inherit functionality to manage init scripts.
inherit update-rc.d

# Init script name and parameters for runlevels.
INITSCRIPT_NAME = "configstartup-sv"
INITSCRIPT_PARAMS = "start 12 1 2 3 4 5 . stop 0 1 6 ."

# Installation instructions for the init script.
do_install() {
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/configstartup-sv ${D}${sysconfdir}/init.d/
}
