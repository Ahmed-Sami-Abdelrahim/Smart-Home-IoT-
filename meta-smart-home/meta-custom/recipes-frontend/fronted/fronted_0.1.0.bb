# License type (CLOSED indicates proprietary software).
LICENSE = "CLOSED"

# Checksum for license files
LIC_FILES_CHKSUM = ""

# Inherit functionality from the npm class to handle Node.js packages.
inherit npm

# Skip the configure step (no configuration required for npm-based projects).
do_configure[noexec] = "1"

# Source URI for fetching the code from a local Git repository.
SRC_URI = "git:///home/ahmedsami/SmartHome-IoT/MERN/client;protocol=file;branch=kirkstone"

# Use the latest commit from the specified branch.
SRCREV = "${AUTOREV}"

# Directory where the source code will be located during the build.
S = "${WORKDIR}/git"

# License type for this package.
LICENSE:${PN} = "Unknown"

# Compile the Node.js project using npm.
do_compile() {
    npm install
    npm run build
}

# Install the built application to the target directory.
do_install() {
    # Create the target directory for the React app.
    install -d ${D}/var/www/react-app
    
    # Copy the built files to the target directory.
    cp -r ${S}/build/* ${D}/var/www/react-app/
}
