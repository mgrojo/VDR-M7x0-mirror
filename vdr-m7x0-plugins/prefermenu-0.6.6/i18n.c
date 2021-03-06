/*
 * PreferMenu plugin to VDR (C++)
 *
 * (C) 2004,2005,2006 Olivier Jacques <oliviervdr@free.fr>
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * Or, point your browser to http://www.gnu.org/copyleft/gpl.html
 */

#include "i18n.h"

const tI18nPhrase Phrases[] = {
/*
 * French  translations provided by Maxime Guilbot <maxime.guilbot@orange.fr>
 */
  { "Channel", // ENGLISH
    "Kanal", // GERMAN
    "", // TODO
    "", // ITALIAN
    "", // NL
    "", // TODO
    "Cha?nes", // FR
    "", // TODO
    "", // TODO
    "", // TODO
    "Canal", // ES
    "", // HU
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
  { "Origin X", // EN
    "Position X", // GERMAN
    "", // TODO
    "", // ITALIAN
    "", // NL
    "", // TODO
    "Origine X", // FR
    "", // TODO
    "", // TODO
    "", // TODO
    "Posici?n X", // ES
    "", // HU
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
  { "Origin Y", // EN
    "Position Y", // GERMAN
    "", // TODO
    "", // ITALIAN 
    "", // NL
    "", // TODO
    "Origine Y", // FR
    "", // TODO
    "", // TODO
    "", // TODO
    "Posici?n Y", // ES
    "", // HU
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
  { "Width", //EN
    "Breite", // GER
    "", // TODO
    "", // ITALIAN
    "", // NL
    "",
    "Largeur", 
    "", // TODO
    "", // TODO
    "", // TODO
    "Ancho", // ES
    "", // HU
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "" // TODO
  },
  { "AddChannel",
    "Kanal hinzuf?gen", // GER
    "", // TODO
    "", // ITALIAN
    "", // NL
    "", // TODO
    "Nouvelle cha?ne",  // FR
    "", // TODO
    "", // TODO
    "", // TODO
    "A?adir canal", // ES
    "", // HU
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "" // TODO
  },
  { "RemoveChannel",
    "Kanal l?schen", // GER
    "", // TODO
    "", // ITALIAN
    "", // NL
    "", // TODO
    "Supprime cha?ne", //FR
    "", // TODO
    "", // TODO
    "", // TODO
    "Borrar canal", // ES
    "", // HU
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "" // TODO
  },
/*
  { "Background opacity",
    "Rand transparenz", // TODO
    "", // TODO
    "", // ITALIAN
    "", // TODO
    "", // TODO
    "Opacit? du fond",
    "", // TODO
    "", // TODO
    "", // TODO
    "Opacidad fondo", // ES
    "", // TODO
  },
  { "Selected channel opacity",
    "", // TODO
    "", // TODO
    "", // ITALIAN
    "", // TODO
    "", // TODO
    "Opacit? de la cha?ne selectionn?e",
    "", // TODO
    "", // TODO
    "", // TODO
    "Opacidad canal seleccionado", // ES
    "", // TODO
  },
  { "Border opacity",
    "Alpha Rand", // GER
    "", // TODO
    "", // ITALIAN
    "", // NL
    "", // TODO
    "Opacit? du contour", // FR
    "", // TODO
    "", // TODO
    "", // TODO
    "Opacidad borde", // ES
    "", // HU
  },
*/
  { "Sort by",
    "", // TODO
    "", // TODO
    "", // ITALIAN
    "", // TODO
    "", // TODO
    "Trier par",
    "", // TODO
    "", // TODO
    "", // TODO
    "Ordenar por", // ES
    "", // TODO
  },
  { "None",
    "", // TODO
    "", // TODO
    "", // ITALIAN
    "", // TODO
    "", // TODO
    "Aucun",
    "", // TODO
    "", // TODO
    "", // TODO
    "Ninguno", // ES
    "", // TODO
  },
  { "Name",
    "", // TODO
    "", // TODO
    "", // ITALIAN
    "", // TODO
    "", // TODO
    "Nom",
    "", // TODO
    "", // TODO
    "", // TODO
    "Nombre", // ES
    "", // TODO
  },
  { "As entered",
    "", // TODO
    "", // TODO
    "", // ITALIAN
    "", // TODO
    "", // TODO
    "Tel que saisi",
    "", // TODO
    "", // TODO
    "", // TODO
    "Seg?n entr?", // ES
    "", // TODO
  },
  { "Close on switch",
    "", // TODO
    "", // TODO
    "", // ITALIAN
    "", // TODO
    "", // TODO
    "Fermer le menu en zappant",
    "", // TODO
    "", // TODO
    "", // TODO
    "Cerrar al cambiar", // ES
    "", // TODO
  },
  { "Number of channels",
    "", // TODO
    "", // TODO
    "", // ITALIAN
    "", // TODO
    "", // TODO
    "",
    "", // TODO
    "", // TODO
    "", // TODO
    "N?mero de canales", // ES
    "", // TODO
  },

 { NULL }
};
