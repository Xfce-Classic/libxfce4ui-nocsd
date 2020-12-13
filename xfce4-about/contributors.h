/*
 * Copyright (C) 2019 Xfce Development Team
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
  { "Alexander Schwinn", "alexxcons@xfce.org" },
  { "Ali Abdallah", "ali@xfce.org" },
  { "Andre Miranda", "andreldm@xfce.org" },
  { "Andrzej Radecki", "ndrwrdck@gmail.com" },
  { "Eric Koegel", "eric@xfce.org" },
  { "Landry Breuil", "landry@xfce.org" },
  { "Olivier Fourdan", "fourdan@xfce.org" },
  { "Romain Bouvier", "skunnyk@alteroot.org" },
  { "Sean Davis", "bluesabre@xfce.org" },
  { "Simon Steinbeiß", "simon@xfce.org" },
  { NULL, NULL}
};

static const ContributorInfo xfce_contributors_active[] =
{
  { "Alistair Buxton", "a.j.buxton@gmail.com" },
  { "Igor", "f2404@yandex.ru" },
  { "Olivier Duchateau", "duchateau.olivier@gmail.com" },
  { "Silvio Knizek", "killermoehre@gmx.net" },
  { "Theo Linkspfeifer", "lastonestanding@tutanota.com" },
  { "Tony Paulic", "tony.paulic@gmail.com" },
  { "Viktor Odintsev", "ninetls@xfce.org" },
  { "Yves-Alexis Perez", "corsac@debian.org" },
  { NULL, NULL }
};

static const ContributorInfo xfce_contributors_server[] =
{
  { "Romain Bouvier", "skunnyk@alteroot.org" },
  { "Mike Massonnet", "mmassonnet@gmail.com" },
  { NULL, NULL }
};

static const ContributorInfo xfce_contributors_translators_supervision[] =
{
  { "Vinzenz Vietzke", "vinz@vinzv.de" },
  { NULL, NULL }
};

static const ContributorInfo xfce_contributors_previous[] =
{
  { "Auke Kok", "sofar@foo-projects.org" },
  { "Benedikt Meurer", "benny@xfce.org" },
  { "Bernhard Walle", "bernhard.walle@gmx.de" },
  { "Biju Chacko", "botsie@xfce.org" },
  { "Brian J. Tarricone", "kelnos@xfce.org" },
  { "Craig Betts", "craig.betts@dfrc.nasa.gov" },
  { "Daichi Kawahata", "daichi@xfce.org" },
  { "Danny Milosavljevic", "dannym@xfce.org" },
  { "Darren Salt", "linux@youmustbejoking.demon.co.uk" },
  { "David Mohr", "squisher@xfce.org" },
  { "Edscott Wilson García", "edscott@xfce.org" },
  { "Eduard Roccatello", "eduard@xfce.org" },
  { "Ejvend Nielsen", "prophet@sphere-x.net" },
  { "Enrico Tröger", "enrico.troeger@uvena.de" },
  { "Erik Harrison", "erikharrison@xfce.org" },
  { "Erik Touve", "etouve@earthlink.net" },
  { "François Le Clainche", "fleclainche@wanadoo.fr" },
  { "Guido Berhoerster", "guido+xfce@berhoerster.name" },
  { "Harald Judt", "hjudt@xfce.org" },
  { "Jannis Pohlmann", "jannis@xfce.org" },
  { "Jasper Huijsmans", "jasper@xfce.org" },
  { "Jean-François Wauthy", "pollux@xfce.org" },
  { "Jens Guballa", "j.guballa@t-online.de" },
  { "Jens Luedicke", "jens@irs-net.com" },
  { "Joakim Andreasson", "joakim.andreasson@gmx.net" },
  { "Jérôme Guelfucci", "jeromeg@xfce.org" },
  { "Karsten Luetkewitz", "phrep@plskthx.org" },
  { "Lionel Le Folgoc", "mrpouit@gmail.com" },
  { "Martin Loschwitz", "madkiss@debian.org" },
  { "Maximilian Schleiss", "maximilian@xfce.org" },
  { "Michael Mosier", "michael@spyonit.com" },
  { "Mickaël Graf", "korbinus@xfce.org" },
  { "Nick Schermer", "nick@xfce.org" },
  { "Pau Rul·lan Ferragut", "paurullan@bulma.net" },
  { "Peter de Ridder", "peter@xfce.org" },
  { "Samuel Verstraete", "elangelo@xfce.org" },
  { "Stephan Arts", "stephan@xfce.org" },
  { "Steve Dodier-Lazaro", "sidi@xfce.org" },
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
  { N_("Translations supervision"),
    xfce_contributors_translators_supervision
  },
  { N_("Translators"),
    NULL
  },
  { N_("Previous contributors"),
    xfce_contributors_previous
  }
};
