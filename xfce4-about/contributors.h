/*
 * Copyright (C) 2010 Xfce Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <gtk/gtk.h>
#include <libxfce4util/libxfce4util.h>

typedef struct
{
  const gchar *name;
  const gchar *email;
}
ContributorInfo;

typedef struct
{
  const gchar           *name;
  const ContributorInfo *contributors;
}
ContributorGroup;

static const ContributorInfo xfce_contributors_core[] =
{
  { "Jannis Pohlmann", "jannis@xfce.org" },
  { "Jérôme Guelfucci", "jeromeg@xfce.org" },
  { "Nick Schermer", "nick@xfce.org" },
  { "Olivier Fourdan", "fourdan@xfce.org" },
  { "Stephan Arts", "stephan@xfce.org" },
  { NULL, NULL }
};

static const ContributorInfo xfce_contributors_active[] =
{
  { "Ali Abdallah", "aliov@xfce.org" },
  { "Andrzej Radecki", "ndrwrdck@gmail.com" },
  { "Benedikt Meurer", "benny@xfce.org" },
  { "Brian J. Tarricone", "kelnos@xfce.org" },
  { "David Mohr", "squisher@xfce.org" },
  { "Enrico Tröger", "enrico.troeger@uvena.de" },
  { "Eric Koegel", "eric@xfce.org" },
  { "Landry Breuil", "landry@openbsd.org" },
  { "Lionel Le Folgoc", "mrpouit@gmail.com" },
  { "Mike Massonnet", "mmassonnet@gmail.com" },
  { "Simon Steinbeiß", "simon@xfce.org" },
  { "Peter de Ridder", "peter@xfce.org" },
  { "Yves-Alexis Perez", "corsac@debian.org" },
  { NULL, NULL }
};

static const ContributorInfo xfce_contributors_server[] =
{
  { "Jean-François Wauthy", "pollux@xfce.org" },
  { "Nick Schermer", "nick@xfce.org" },
  { "Samuel Verstraete", "elangelo@xfce.org" },
  { NULL, NULL }
};

static const ContributorInfo xfce_contributors_goodies_supervision[] =
{
  { "Jannis Pohlmann", "jannis@xfce.org" },
  { NULL, NULL }
};

static const ContributorInfo xfce_contributors_translators_supervision[] =
{
  { "Mike Massonnet", "mmassonnet@gmail.com" },
  { NULL, NULL }
};

static const ContributorInfo xfce_contributors_previous[] =
{
  { "Auke Kok", "sofar@foo-projects.org" },
  { "Bernhard Walle", "bernhard.walle@gmx.de" },
  { "Biju Chacko", "botsie@xfce.org" },
  { "Craig Betts", "craig.betts@dfrc.nasa.gov" },
  { "Daichi Kawahata", "daichi@xfce.org" },
  { "Danny Milosavljevic", "dannym@xfce.org" },
  { "Darren Salt", "linux@youmustbejoking.demon.co.uk" },
  { "Edscott Wilson García", "edscott@xfce.org" },
  { "Eduard Roccatello", "eduard@xfce.org" },
  { "Ejvend Nielsen", "prophet@sphere-x.net" },
  { "Erik Touve", "etouve@earthlink.net" },
  { "Erik Harrison", "erikharrison@xfce.org" },
  { "François Le Clainche", "fleclainche@wanadoo.fr" },
  { "Jasper Huijsmans", "jasper@xfce.org" },
  { "Jean-François Wauthy", "pollux@xfce.org" },
  { "Jens Guballa", "j.guballa@t-online.de" },
  { "Jens Luedicke", "jens@irs-net.com" },
  { "Joakim Andreasson", "joakim.andreasson@gmx.net" },
  { "Karsten Luetkewitz", "phrep@plskthx.org" },
  { "Martin Loschwitz", "madkiss@debian.org" },
  { "Maximilian Schleiss", "maximilian@xfce.org" },
  { "Michael Mosier", "michael@spyonit.com" },
  { "Mickaël Graf", "korbinus@xfce.org" },
  { "Pau Rul·lan Ferragut", "paurullan@bulma.net" },
  { "Thomas Leonard", "tal00r@ecs.soton.ac.uk" },
  { "Tobias Henle", "tobias@page23.de" },
  { "Xavier Maillard", "zedek@fxgsproject.org" },
  { NULL, NULL }
};

static const ContributorGroup xfce_contributors[] =
{
  /*{ N_("Project Lead"),
    xfce_contributors_lead
  },*/
  { N_("Core developers"),
    xfce_contributors_core
  },
  { N_("Active contributors"),
    xfce_contributors_active
  },
  { N_("Servers maintained by"),
    xfce_contributors_server
  },
  { N_("Goodies supervision"),
    xfce_contributors_goodies_supervision
  },
  { N_("Translations supervision"),
    xfce_contributors_translators_supervision
  },
  { N_("Translators"),
    NULL /* data from translators.h will be used here */
  },
  { N_("Previous contributors"),
    xfce_contributors_previous
  }
};
