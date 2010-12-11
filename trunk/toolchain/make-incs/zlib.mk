# Copyright (C) 2006,2007 Andreas Koch - the open7x0.org group
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
# Or, point your browser to http://www.gnu.org/copyleft/gpl.html
#
# The author can be reached at andreas@open7x0.org
#
# The project's page is at http://www.open7x0.org
#
# $Id: zlib.mk 401 2009-03-26 12:29:09Z andreas $
#

ZLIB_DEPS = $(BASE_BUILD_STAGEFILE)

ZLIB_VERSION := 1.2.3
ZLIB_PATCHES_DIR := $(PATCHES_DIR)/zlib/$(ZLIB_VERSION)

ZLIB_FILE := zlib-$(ZLIB_VERSION).tar.bz2
ZLIB_DLFILE := $(DOWNLOAD_DIR)/$(ZLIB_FILE)
ZLIB_DIR := $(BUILD_DIR)/zlib-$(ZLIB_VERSION)
ZLIB_URL := http://sourceforge.net/projects/libpng/files/zlib/$(ZLIB_VERSION)/$(ZLIB_FILE)/download

ZLIB_INSTALLED = $(STAGEFILES_DIR)/.zlib_installed

PACKS_RULES_$(CONFIG_ZLIB_STATIC) += $(STAGEFILES_DIR)/.zlib_static_installed
PACKS_RULES_$(CONFIG_ZLIB) += $(ZLIB_INSTALLED)

FILE_LISTS_$(CONFIG_ZLIB) += zlib.lst

CLEAN_RULES += clean-zlib
DISTCLEAN_RULES += distclean-zlib

#
# download zlib
#

$(ZLIB_DLFILE): $(TC_INIT_RULE)
	(if [ ! -f $(ZLIB_DLFILE) ] ; then \
	$(WGET) $(ZLIB_URL) -O $(ZLIB_DLFILE) ; \
	fi );
	$(TOUCH) $(ZLIB_DLFILE)

#
# unpack zlib
#

$(STAGEFILES_DIR)/.zlib_unpacked: $(ZLIB_DLFILE) $(ZLIB_PATCHES_DIR)/*.patch \
                                  $$(ZLIB_DEPS)
	-$(RM) -rf $(ZLIB_DIR)
	$(BZCAT) $(ZLIB_DLFILE) | $(TAR) -C $(BUILD_DIR) -f -
	$(TOUCH) $(STAGEFILES_DIR)/.zlib_unpacked

#
# patch zlib
#

$(STAGEFILES_DIR)/.zlib_patched: $(STAGEFILES_DIR)/.zlib_unpacked
	$(call patch_package, $(ZLIB_DIR), $(ZLIB_PATCHES_DIR))
	$(TOUCH) $(STAGEFILES_DIR)/.zlib_patched

#
# configure zlib
#

$(STAGEFILES_DIR)/.zlib_configured: $(STAGEFILES_DIR)/.zlib_patched \
                                    $(subst y, \
                                      $(STAGEFILES_DIR)/.zlib_static_installed, \
                                      $(filter y,$(CONFIG_ZLIB_STATIC)))
	# -$(RM) -f $(STAGEFILES_DIR)/.zlib_static_configured
	-$(UCLIBC_ENV) $(MAKE) -C $(ZLIB_DIR) distclean
	($(CD) $(ZLIB_DIR) ; $(UCLIBC_ENV) \
		$(ZLIB_DIR)/configure \
			--prefix=$(TARGET_ROOT)/usr \
			--shared) # This is really needed otherwise _only_ static is build
	$(TOUCH) $(STAGEFILES_DIR)/.zlib_configured

#
# compile zlib
#

$(STAGEFILES_DIR)/.zlib_compiled: $(STAGEFILES_DIR)/.zlib_configured
	$(UCLIBC_ENV) $(MAKE) -C $(ZLIB_DIR) all
	$(TOUCH) $(STAGEFILES_DIR)/.zlib_compiled

#
# install zlib
#

$(STAGEFILES_DIR)/.zlib_installed: $(STAGEFILES_DIR)/.zlib_compiled
	$(UCLIBC_ENV) $(MAKE) -C $(ZLIB_DIR) install
	$(TOUCH) $(STAGEFILES_DIR)/.zlib_installed

#
# configure static zlib
#

$(STAGEFILES_DIR)/.zlib_static_configured: $(STAGEFILES_DIR)/.zlib_patched
	# -$(RM) -f $(STAGEFILES_DIR)/.zlib_configured
	-$(UCLIBC_ENV) $(MAKE) -C $(ZLIB_DIR) distclean
	($(CD) $(ZLIB_DIR) ; $(UCLIBC_ENV) \
		$(ZLIB_DIR)/configure \
			--prefix=$(TARGET_ROOT)/usr)
	$(TOUCH) $(STAGEFILES_DIR)/.zlib_static_configured

#
# compile static zlib
#

$(STAGEFILES_DIR)/.zlib_static_compiled: $(STAGEFILES_DIR)/.zlib_static_configured
	$(UCLIBC_ENV) $(MAKE) -C $(ZLIB_DIR) all
	$(TOUCH) $(STAGEFILES_DIR)/.zlib_static_compiled

#
# install static zlib
#

$(STAGEFILES_DIR)/.zlib_static_installed: $(STAGEFILES_DIR)/.zlib_static_compiled
	$(UCLIBC_ENV) $(MAKE) -C $(ZLIB_DIR) install
	$(TOUCH) $(STAGEFILES_DIR)/.zlib_static_installed

$(FILELIST_DIR)/zlib.lst: $(STAGEFILES_DIR)/.zlib_installed
	$(TOUCH) $(FILELIST_DIR)/zlib.lst

.PHONY: clean-zlib distclean-zlib

clean-zlib-uclibc:
	-$(RM) -rf $(ZLIB_DIR)

distclean-zlib-uclibc:
	-$(RM) -f $(STAGEFILES_DIR)/.zlib_unpacked
	-$(RM) -f $(STAGEFILES_DIR)/.zlib_patched
	-$(RM) -f $(STAGEFILES_DIR)/.zlib_configured
	-$(RM) -f $(STAGEFILES_DIR)/.zlib_compiled
	-$(RM) -f $(STAGEFILES_DIR)/.zlib_installed
ifeq ($(DISTCLEAN_DLFILE),y)
	-$(RM) -rf $(ZLIB_DLFILE)
endif
