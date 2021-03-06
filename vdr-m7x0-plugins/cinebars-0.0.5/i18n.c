/*
 * i18n.c Internationalization - part of cinebars.c, a plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include "i18n.h"

const tI18nPhrase Phrases[] = {
  { "Overlays \"cinebars\"",		// English
    "legt \"Kinobalken\" aufs Bild",	// Deutsch
    "",// Slovenski
    "",// Italiano
    "",// Nederlands
    "",// Portugu?s
    "",// Fran?ais
    "",// Norsk
    "",// suomi
    "",// Polski
    "Superposici?n \"bandas de cine\"",	// Espa?ol
    "",// ????????
    "",// Svenska
    "",// Romaneste
    "",// Magyar
    "",// Catal?
#if VDRVERSNUM >= 10300
    "" // ???????
#endif
  },
  { "Cinebars",		// English
    "Kinobalken",	// Deutsch
    "",// Slovenski
    "",// Italiano
    "",// Nederlands
    "",// Portugu?s
    "",// Fran?ais
    "",// Norsk
    "",// suomi
    "",// Polski
    "Bandas de cine",	// Espa?ol
    "",// ????????
    "",// Svenska
    "",// Romaneste
    "",// Magyar
    "",// Catal?
#if VDRVERSNUM >= 10300
    "" // ???????
#endif
  },
  { "Hide mainmenu entry", 			// English
    "Hauptmen?eintrag verstecken", 		// Deutsch
    "", // Slovenski
    "", 	// Italiano
    "", // Nederlands
    "", // Portugu?s
    "", // Fran?ais
    "", // Norsk
    "", 		// suomi
    "", // Polski
    "Ocultar entrada en men? principal",	// Espa?ol
    "", // ????????
    "", // Svenska
    "", // Romaneste
    "", // Magyar
    "", // Catal?
#if VDRVERSNUM >= 10300
    ""  // TODO
#endif
  },
  { "Top Bar",
    "Balken Oben",
    "",// TODO
    "",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",
    "",// TODO
    "Banda superior",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
#if VDRVERSNUM >= 10300
    "" // TODO
#endif
  },
  { "Top BarHeight",
    "Balkenh?he Oben",
    "",// TODO
    "",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",
    "",// TODO
    "Altura banda superior",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
#if VDRVERSNUM >= 10300
    "" // TODO
#endif
  },
  { "Bottom Bar",
    "Balken Unten",
    "",// TODO
    "",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",
    "",// TODO
    "Banda inferior",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
#if VDRVERSNUM >= 10300
    "" // TODO
#endif
  },
  { "Bottom BarHeight",
    "Balkenh?he Unten",
    "",// TODO
    "",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",
    "",// TODO
    "Altura banda inferior",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
#if VDRVERSNUM >= 10300
    "" // TODO
#endif
  },
  { "StepHeight",
    "Schrittweite H?he",
    "",// TODO
    "",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",
    "",// TODO
    "Incremento de altura",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
#if VDRVERSNUM >= 10300
    "" // TODO
#endif
  },
  { "OSD-Mode",
    "OSD-Modus",
    "",// TODO
    "",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",
    "",// TODO
    "Modo OSD",
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
    "",// TODO
#if VDRVERSNUM >= 10300
    "" // TODO
#endif
  },
  { NULL }
  };
