LICENSE = "CLOSED"

# Source URI for fetching the source code from a local Git repository.
SRC_URI = "git:///home/ahmedsami/SmartHome-IoT/device-control;protocol=file;branch=kirkstone"

# Source revision; AUTOREV fetches the latest commit from the branch.
SRCREV = "${AUTOREV}"

# Source directory during the build process.
S = "${WORKDIR}/git"

# Inherit functionality from the cmake class to handle CMake-based builds.
inherit cmake
