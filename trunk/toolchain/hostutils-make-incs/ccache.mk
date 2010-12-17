# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#
# The project's page is at http://www.open7x0.org
#
#

CCACHE_HOSTVERSION := 3.1.3
CCACHE_HOSTFILE := ccache-$(CCACHE_HOSTVERSION).tar.gz
CCACHE_HOSTDLFILE := $(DOWNLOAD_DIR)/$(CCACHE_HOSTFILE)

CCACHE_HOSTPATCHES_DIR := $(PATCHES_DIR)/ccache/$(CCACHE_HOSTVERSION)
CCACHE_HOSTURL := http://samba.org/ftp/ccache/$(CCACHE_HOSTFILE)
CCACHE_HOSTDIR := $(HOSTUTILS_BUILD_DIR)/ccache-$(CCACHE_HOSTVERSION)
CCACHE_HOSTINSTALLED = $(STAGEFILES_DIR)/.ccache_host_installed

CLEAN_RULES += clean-ccache-host
DISTCLEAN_RULES += distclean-ccache-host

#
# download ccache
#

$(CCACHE_HOSTDLFILE): $(TC_INIT_RULE)
	(if [ ! -f $(CCACHE_HOSTDLFILE) ] ; then \
	$(WGET) $(CCACHE_HOSTURL) -O $(CCACHE_HOSTDLFILE) ; \
	fi );
	$(TOUCH) $(CCACHE_HOSTDLFILE)

#
# unpack ccache
#

$(STAGEFILES_DIR)/.ccache_host_unpacked: $(CCACHE_HOSTDLFILE) \
                                         	$(wildcard $(CCACHE_HOSTPATCHES_DIR)/*.patch)
	-$(RM) -rf $(CCACHE_HOSTDIR)
	$(TAR) -C $(HOSTUTILS_BUILD_DIR) -zf $(CCACHE_HOSTDLFILE)
	$(TOUCH) $(STAGEFILES_DIR)/.ccache_host_unpacked

#
# patch ccache
#

$(STAGEFILES_DIR)/.ccache_host_patched: $(STAGEFILES_DIR)/.ccache_host_unpacked
	$(call patch_package, $(CCACHE_HOSTDIR), $(CCACHE_HOSTPATCHES_DIR))
	$(TOUCH) $(STAGEFILES_DIR)/.ccache_host_patched

#
# configure ccache
#

$(STAGEFILES_DIR)/.ccache_host_configured: $(STAGEFILES_DIR)/.ccache_host_patched
	-$(MAKE) -C $(CCACHE_HOSTDIR) distclean
	($(CD) $(CCACHE_HOSTDIR) ; \
		$(CCACHE_HOSTDIR)/configure \
			--prefix=$(PREFIX))
	$(TOUCH) $(STAGEFILES_DIR)/.ccache_host_configured

#
# compile ccache
#

$(STAGEFILES_DIR)/.ccache_host_compiled: $(STAGEFILES_DIR)/.ccache_host_configured
	-$(MAKE) -C $(CCACHE_HOSTDIR) clean
	$(MAKE) -C $(CCACHE_HOSTDIR) all
	$(TOUCH) $(STAGEFILES_DIR)/.ccache_host_compiled

#
# install ccache
#

$(STAGEFILES_DIR)/.ccache_host_installed: $(STAGEFILES_DIR)/.ccache_host_compiled
	-$(RM) -rf $(PREFIX_BIN)/ccache
	$(MKDIR) -p $(PREFIX_BIN)/ccache
	$(CP) $(CCACHE_HOSTDIR)/ccache $(PREFIX_BIN)/ccache/ccache
	$(LN) -sf $(PREFIX_BIN)/ccache/ccache $(PREFIX_BIN)/ccache/$(UCLIBC_CC)
	$(LN) -sf $(PREFIX_BIN)/ccache/ccache $(PREFIX_BIN)/ccache/$(UCLIBC_CXX)
	$(TOUCH) $(STAGEFILES_DIR)/.ccache_host_installed

.PHONY: clean-ccache-host distclean-ccache-host

clean-ccache-host:
	-$(RM) -rf $(CCACHE_HOSTDIR)

distclean-ccache-host:
	-$(RM) -f $(STAGEFILES_DIR)/.ccache_host_unpacked
	-$(RM) -f $(STAGEFILES_DIR)/.ccache_host_patched
	-$(RM) -f $(STAGEFILES_DIR)/.ccache_host_configured
	-$(RM) -f $(STAGEFILES_DIR)/.ccache_host_compiled
	-$(RM) -f $(STAGEFILES_DIR)/.ccache_host_installed
ifeq ($(DISTCLEAN_DLFILE),y)
	-$(RM) -rf $(CCACHE_HOSTDLFILE)
endif