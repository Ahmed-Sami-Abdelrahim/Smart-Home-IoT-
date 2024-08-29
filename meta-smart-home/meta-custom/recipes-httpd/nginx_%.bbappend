# Add a directory for additional files specific to this recipe.
FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

# Add a local file to the source URI for the build.
SRC_URI += "file://default_server"

# Append to the install step to include custom file installation.
do_install:append() {
    # Install the default_server file with specific permissions.
    install -m 0644 ${WORKDIR}/default_server ${D}${sysconfdir}/nginx/sites-available/
}
