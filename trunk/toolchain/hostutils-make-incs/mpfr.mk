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
# The project's page is at http://www.open7x0.org
#

# Put dependencies here
MPFR_HOSTDEPS = $(GMP_HOSTINSTALLED)

MPFR_HOSTVERSION := 3.1.0
MPFR_HOSTPATCHES_DIR := $(PATCHES_DIR)/mpfr/$(MPFR_HOSTVERSION)

MPFR_HOSTFILE := mpfr-$(MPFR_HOSTVERSION).tar.bz2
MPFR_HOSTDLFILE := $(DOWNLOAD_DIR)/$(MPFR_HOSTFILE)
MPFR_HOSTURL := http://www.mpfr.org/mpfr-$(MPFR_HOSTVERSION)/$(MPFR_HOSTFILE)
MPFR_HOSTDIR := $(HOSTUTILS_BUILD_DIR)/mpfr-$(MPFR_HOSTVERSION)

MPFR_HOSTINSTALLED = $(STAGEFILES_DIR)/.mpfr_host_installed

PACKS_RULES_$(CONFIG_MPFR) += $(MPFR_HOSTINSTALLED)

CLEAN_RULES += clean-mpfr
DISTCLEAN_RULES += distclean-mpfr

#
# download mpfr
#

$(MPFR_HOSTDLFILE): $(TC_INIT_RULE)
	(if [ ! -f $(MPFR_HOSTDLFILE) ] ; then \
	$(WGET) $(MPFR_HOSTURL) -O $(MPFR_HOSTDLFILE) ; \
	fi );
	$(TOUCH) $(MPFR_HOSTDLFILE)

#
# unpack mpfr
#

$(STAGEFILES_DIR)/.mpfr_host_unpacked: $(MPFR_HOSTDLFILE) \
                                           $(wildcard $(MPFR_HOSTPATCHES_DIR)/*.patch) \
                                           $$(MPFR_HOSTDEPS)
	-$(RM) -rf $(MPFR_HOSTDIR)
	$(BZCAT) $(MPFR_HOSTDLFILE) | $(TAR) -C $(HOSTUTILS_BUILD_DIR) -f -
	$(TOUCH) $(STAGEFILES_DIR)/.mpfr_host_unpacked

#
# patch mpfr
#

$(STAGEFILES_DIR)/.mpfr_host_patched: $(STAGEFILES_DIR)/.mpfr_host_unpacked
	$(call patch_package, $(MPFR_HOSTDIR), $(MPFR_HOSTPATCHES_DIR))
	$(TOUCH) $(STAGEFILES_DIR)/.mpfr_host_patched

#
# configure mpfr
#

$(STAGEFILES_DIR)/.mpfr_host_configured: $(STAGEFILES_DIR)/.mpfr_host_patched
	($(CD) $(MPFR_HOSTDIR) ; $(MPFR_HOSTDIR)/configure \
			--prefix=$(PREFIX) \
			--enable-static \
			--disable-shared \
			--with-gmp=$(PREFIX))
	$(TOUCH) $(STAGEFILES_DIR)/.mpfr_host_configured

#
# compile mpfr
#

$(STAGEFILES_DIR)/.mpfr_host_compiled: $(STAGEFILES_DIR)/.mpfr_host_configured
	$(MAKE) -C $(MPFR_HOSTDIR)
	$(TOUCH) $(STAGEFILES_DIR)/.mpfr_host_compiled

#
# install mpfr
#

$(STAGEFILES_DIR)/.mpfr_host_installed: $(STAGEFILES_DIR)/.mpfr_host_compiled
	$(MAKE) -C $(MPFR_HOSTDIR) install
	$(TOUCH) $(STAGEFILES_DIR)/.mpfr_host_installed


.PHONY: clean-mpfr distclean-mpfr

clean-mpfr:
	-$(RM) -rf $(MPFR_HOSTDIR)

#
# clean everthing else
#

distclean-mpfr:
	-$(RM) -f $(STAGEFILES_DIR)/.mpfr_host_unpacked
	-$(RM) -f $(STAGEFILES_DIR)/.mpfr_host_patched
	-$(RM) -f $(STAGEFILES_DIR)/.mpfr_host_configured
	-$(RM) -f $(STAGEFILES_DIR)/.mpfr_host_compiled
	-$(RM) -f $(STAGEFILES_DIR)/.mpfr_host_installed
ifeq ($(DISTCLEAN_DLFILE),y)
	-$(RM) -rf $(MPFR_HOSTDLFILE)
endif
