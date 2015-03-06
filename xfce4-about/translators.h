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

#define TRANSLATORS_H_STAMP "2015-03-06 11:34:46"
#define ATSIGN "@"
#define DOTSIGN "."

typedef struct
{
  const gchar *name;
  const gchar *email;
  guint        is_coordinator : 1;
}
TranslatorInfo;

typedef struct
{
  const gchar          *name;
  const gchar          *code;
  const TranslatorInfo *members;
}
TranslatorTeam;


/* Amharic */
static const TranslatorInfo xfce_translators_am[] =
{
  { "Belay", "belaytekalign" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Tegegne Tefera", "tefera" ATSIGN "mekuria" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Arabic */
static const TranslatorInfo xfce_translators_ar[] =
{
  { "عبدالله رضوان", "abbodmar" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "كريم أولاد الشلحة", "herr" DOTSIGN "linux88" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "abdXelrhman", "abdxelrhman" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "محمد الحرقان", "malham1" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ahmadzxc", "ahmad" DOTSIGN "almomani5" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Amine", "amine" ATSIGN "linuxac" DOTSIGN "org", FALSE },
  { "M. Fawwaz Orabi", "mfawwaz93" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "M.hanny Sabbagh", "hannysabbagh" ATSIGN "hotmail" DOTSIGN "com", FALSE },
  { "Mohsen", "linuxer9" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Noureddin Khatat", "noureddin" ATSIGN "barid" DOTSIGN "com", FALSE },
  { "Simohamed", "mohamed" DOTSIGN "sakhri" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Asturian */
static const TranslatorInfo xfce_translators_ast[] =
{
  { "Enolp", "enolp" ATSIGN "softastur" DOTSIGN "org", FALSE },
  { "Iñigo Varela", "malditoastur" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Tornes Llume", "l" DOTSIGN "lumex03" DOTSIGN "tornes" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Belarusian */
static const TranslatorInfo xfce_translators_be[] =
{
  { "Andrei Zakharevich", "andrej" ATSIGN "zahar" DOTSIGN "ws", FALSE },
  { "Mikalai Udodau", "crom-a" ATSIGN "tut" DOTSIGN "by", FALSE },
  { "Mike Gelfand", "mikedld" ATSIGN "mikedld" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Bulgarian */
static const TranslatorInfo xfce_translators_bg[] =
{
  { "Gazarrr", "gazarrr" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Georgi Georgiev", "georgiev_1994" ATSIGN "abv" DOTSIGN "bg", FALSE },
  { "Kiril Kirilov", "cybercop_montana" ATSIGN "abv" DOTSIGN "bg", FALSE },
  { "Krasimir Chonov", "mk2616" ATSIGN "abv" DOTSIGN "bg", FALSE },
  { "Milen Milev", "fanfolet" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Valentin Tunev", "hdbuster" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Bengali */
static const TranslatorInfo xfce_translators_bn[] =
{
  { "Jamil Ahmed", "itsjamil" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Catalan */
static const TranslatorInfo xfce_translators_ca[] =
{
  { "Alavios", "registres" ATSIGN "lavios" DOTSIGN "cat", FALSE },
  { "Carles Muñoz Gorriz", "carlesmu" ATSIGN "internautas" DOTSIGN "org", FALSE },
  { "Frangor", "frangor" ATSIGN "frangor" DOTSIGN "info", FALSE },
  { "Harald Servat", "redcrash" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Joan Montané", "joan" ATSIGN "montane" DOTSIGN "cat", FALSE },
  { "Lebrush", "lebrush" ATSIGN "xplosio" DOTSIGN "net", FALSE },
  { "Paul Garden", "kiari62" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Roger Pueyo Centelles", "xfce" ATSIGN "rogerpueyo" DOTSIGN "com", FALSE },
  { "Sandandmercury", "sandandmercury" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Czech */
static const TranslatorInfo xfce_translators_cs[] =
{
  { "Alois Nešpor", "info" ATSIGN "aloisnespor" DOTSIGN "info", FALSE },
  { "Franti3ek", "frantisek" DOTSIGN "komarek" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Fri", "pavelfric" ATSIGN "seznam" DOTSIGN "cz", FALSE },
  { "Libor Schejbal", "libor" DOTSIGN "schejbal" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Michal Várady", "miko" DOTSIGN "vaji" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Per Kongstad", "p_kongstad" ATSIGN "op" DOTSIGN "pl", FALSE },
  { "Radim Kolář", "kolar" DOTSIGN "radim" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Robert Hartl", "hartl" DOTSIGN "robert" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Danish */
static const TranslatorInfo xfce_translators_da[] =
{
  { "Aputsiaĸ Niels Janussen", "aj" ATSIGN "isit" DOTSIGN "gl", FALSE },
  { "Chris Darnell", "chris" ATSIGN "cedeel" DOTSIGN "com", FALSE },
  { "Erik Schmidt", "erischmi" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Kris Thomsen", "lakristho" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Morten Juhl-Johansen Zölde-Fejér", "mjjzf" ATSIGN "syntaktisk" DOTSIGN "dk", FALSE },
  { "Per Kongstad", "p_kongstad" ATSIGN "op" DOTSIGN "pl", FALSE },
  { NULL, NULL }
};


/* German */
static const TranslatorInfo xfce_translators_de[] =
{
  { "Chris Leick", "c" DOTSIGN "leick" ATSIGN "vollbio" DOTSIGN "de", FALSE },
  { "Christoph Mende", "angelos" ATSIGN "gentoo" DOTSIGN "org", FALSE },
  { "Christoph Wickert", "christoph" DOTSIGN "wickert" ATSIGN "googlemail" DOTSIGN "com", FALSE },
  { "David Mohr", "david" ATSIGN "mcbf" DOTSIGN "net", FALSE },
  { "Detlef Riekenberg", "wine" DOTSIGN "dev" ATSIGN "web" DOTSIGN "de", FALSE },
  { "Fabian Nowak", "timystery" ATSIGN "arcor" DOTSIGN "de", FALSE },
  { "Georg Eckert", "eckert" DOTSIGN "georg" ATSIGN "gmx" DOTSIGN "de", FALSE },
  { "Harald Judt", "h" DOTSIGN "judt" ATSIGN "gmx" DOTSIGN "at", FALSE },
  { "Jakob Kramer", "jakob" DOTSIGN "kramer" ATSIGN "gmx" DOTSIGN "de", FALSE },
  { "Jannis Pohlmann", "jannis" ATSIGN "xfce" DOTSIGN "org", FALSE },
  { "Johannes Lips", "johannes" DOTSIGN "lips" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Mario Blättermann", "mario" DOTSIGN "blaettermann" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Mark Trompell", "mark" ATSIGN "foresightlinux" DOTSIGN "org", FALSE },
  { "Michael Spahn", "any0n3" ATSIGN "fedoraproject" DOTSIGN "org", FALSE },
  { "Paul Seyfert", "pseyfert" ATSIGN "mathphys" DOTSIGN "fsk" DOTSIGN "uni-heidelberg" DOTSIGN "de", FALSE },
  { "Raphael Groner", "raphgro" ATSIGN "web" DOTSIGN "de", FALSE },
  { "Roland Kübert", "roland" ATSIGN "upic" DOTSIGN "de", FALSE },
  { "Simon Steinbeiss", "ochosi" ATSIGN "xfce" DOTSIGN "org", FALSE },
  { "Thomas Schütz", "xfce" ATSIGN "thschuetz" DOTSIGN "de", FALSE },
  { "Tobias Bannert", "tobannert" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Uwe Krause", "derhorst" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Greek */
static const TranslatorInfo xfce_translators_el[] =
{
  { "Efstathios Iosifidis", "iefstathios" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Evaggelos Balaskas", "ebalaskas" ATSIGN "ebalaskas" DOTSIGN "gr", FALSE },
  { "Forfolias", "forfolias" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Gapan", "vlahavas" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Georgios Stefanakis", "nonviotale" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Jani Kotsionis", "ikotsionis" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Klearchos-Angelos Gkountras", "kleagkou" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Loathingkernel", "zeronebones" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Madits", "dimitsas" DOTSIGN "markos" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Mario Andonoudiou", "supermodmusic" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Spiros Georgaras", "sng" ATSIGN "hellug" DOTSIGN "gr", FALSE },
  { "Spyros", "spyros_stravoravdis" ATSIGN "hotmail" DOTSIGN "com", FALSE },
  { "Stavros Giannouris", "stavrosg" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* English (Australia) */
static const TranslatorInfo xfce_translators_en_AU[] =
{
  { "Michael Findlay", "keltoiboy" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* English (Great Britain) */
static const TranslatorInfo xfce_translators_en_GB[] =
{
  { "Jeff Bailes", "thepizzaking" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Noskcaj", "noskcaj" ATSIGN "ubuntu" DOTSIGN "com", FALSE },
  { "Readmanr", "robert_readman" ATSIGN "hotmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Esperanto */
static const TranslatorInfo xfce_translators_eo[] =
{
  { "Aleksandr Ponomarenko", "davian818" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Edsono", "edsono" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Spanish */
static const TranslatorInfo xfce_translators_es[] =
{
  { "Abel Martín", "abel" DOTSIGN "martin" DOTSIGN "ruiz" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Adolfo Jayme Barrientos", "fitoschido" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Andres Sanchez", "afsanchez93" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "César Enrique García", "cquike" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "David Segura Monroy", "davidseg" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Edwinpm5", "edwinpm5" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Francisco Javier Serrador", "fserrador" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Gabrieltandil", "gabriel" DOTSIGN "tandil" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Gonzalo Lagos", "xalo" DOTSIGN "em" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Hernan Gabriel Alvarez Guerra", "hernan" DOTSIGN "alvarez" DOTSIGN "guerra" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ignacio Velasco", "elega" ATSIGN "elega" DOTSIGN "com" DOTSIGN "ar", FALSE },
  { "Javier Sánchez Reinosa", "donoban" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Lbazan", "bazanluis20" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Manolo Díaz", "diaz" DOTSIGN "manolo" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "MC", "correomc2000-ing" ATSIGN "yahoo" DOTSIGN "es", FALSE },
  { "Pablo Lezaeta", "prflr88" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Pharamir", "pamirmatos" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sergio García", "oigres200" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "The Idiot", "brian" DOTSIGN "peraza" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Estonian */
static const TranslatorInfo xfce_translators_et[] =
{
  { "Allar Kiristaja", "aquastus" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Mattias Põldaru", "mahfiaz" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Basque */
static const TranslatorInfo xfce_translators_eu[] =
{
  { "Asier Iturralde Sarasola", "asier" DOTSIGN "iturralde" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Piarres Beobide", "pi" ATSIGN "beobide" DOTSIGN "net", FALSE },
  { NULL, NULL }
};


/* Persian */
static const TranslatorInfo xfce_translators_fa[] =
{
  { "Mehdi Esmaeelpour", "ariarat" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Finnish */
static const TranslatorInfo xfce_translators_fi[] =
{
  { "Flammie Pirinen", "flammie" ATSIGN "iki" DOTSIGN "fi", FALSE },
  { "Jari Rahkonen", "jari" DOTSIGN "rahkonen" ATSIGN "pp1" DOTSIGN "inet" DOTSIGN "fi", FALSE },
  { "Jarno Liimatainen", "jarliim" ATSIGN "iki" DOTSIGN "fi", FALSE },
  { "Jiri Grönroos", "jiri" DOTSIGN "gronroos" ATSIGN "iki" DOTSIGN "fi", FALSE },
  { "Juhani Numminen", "juhaninumminen0" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Lasse Liehu", "larso" ATSIGN "gmx" DOTSIGN "com", FALSE },
  { "Pasi Lallinaho", "pasi" ATSIGN "shimmerproject" DOTSIGN "org", FALSE },
  { "Tapio Väisänen", "tapio" DOTSIGN "vaeisaenen" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Tero Mononen", "tero" ATSIGN "mononen" DOTSIGN "eu", FALSE },
  { NULL, NULL }
};


/* French */
static const TranslatorInfo xfce_translators_fr[] =
{
  { "Anthony Jorion", "pingax" ATSIGN "frugalware" DOTSIGN "fr", FALSE },
  { "Benoit Thibaud", "frombenny" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Douart Patrick", "patrick" DOTSIGN "2" ATSIGN "laposte" DOTSIGN "net", FALSE },
  { "Durand-Favreau Arnaud", "biginoz" ATSIGN "free" DOTSIGN "fr", FALSE },
  { "Fevrier", "jean-philippe" DOTSIGN "guerard" ATSIGN "tigreraye" DOTSIGN "org", FALSE },
  { "Filorin", "guillaume" DOTSIGN "ber17" ATSIGN "laposte" DOTSIGN "net", FALSE },
  { "Glaville", "laville" DOTSIGN "guillaume" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Iliyas Jorio", "inv" DOTSIGN "jorio" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Jc Jc1", "jc1" DOTSIGN "quebecos" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Jean-Philippe Fleury", "contact" ATSIGN "jpfleury" DOTSIGN "net", FALSE },
  { "Jérôme Guelfucci", "jeromeg" ATSIGN "xfce" DOTSIGN "org", FALSE },
  { "Louis Moureaux", "m_louis30" ATSIGN "yahoo" DOTSIGN "com", FALSE },
  { "Mario Gervais", "gervais" DOTSIGN "mario" ATSIGN "ymail" DOTSIGN "com", FALSE },
  { "Maximilian Schleiss", "maximilian" ATSIGN "xfce" DOTSIGN "org", FALSE },
  { "Mike Massonnet", "mmassonnet" ATSIGN "xfce" DOTSIGN "org", FALSE },
  { "Pedwo51", "pedwo51" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Pingax", "pingax" ATSIGN "frugalware" DOTSIGN "org", FALSE },
  { "Remi Andruccioli", "remi" DOTSIGN "andruccioli" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Steve Dodier", "sidnioulz" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Urien Desterres", "urien" DOTSIGN "desterres" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Xavier Devlamynck", "magicrhesus" ATSIGN "ouranos" DOTSIGN "be", FALSE },
  { "Yannick Le Guen", "leguen" DOTSIGN "yannick" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Galician */
static const TranslatorInfo xfce_translators_gl[] =
{
  { "Leandro Regueiro", "leandro" DOTSIGN "regueiro" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Hebrew */
static const TranslatorInfo xfce_translators_he[] =
{
  { "GenghisKhan", "genghiskhan" ATSIGN "gmx" DOTSIGN "ca", FALSE },
  { "Hezy Amiel", "open" ATSIGN "hezyamiel" DOTSIGN "com", FALSE },
  { "Nick Vurgaft", "slipperygate" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Yaron Shahrabani", "sh" DOTSIGN "yaron" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Croatian */
static const TranslatorInfo xfce_translators_hr[] =
{
  { "Denis Štogl", "denisstogl" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Edin Veskovic", "edin" DOTSIGN "veskovic" ATSIGN "openmailbox" DOTSIGN "org", FALSE },
  { "Ivica  Kolić", "ikoli" ATSIGN "yahoo" DOTSIGN "com", FALSE },
  { "Petar Koretić", "petar" DOTSIGN "koretic" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Hungarian */
static const TranslatorInfo xfce_translators_hu[] =
{
  { "Gabor Kelemen", "kelemeng" ATSIGN "gnome" DOTSIGN "hu", FALSE },
  { "Gyönki Bendegúz", "gyonkibendeguz" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Imre Benedek", "nucleo" ATSIGN "indamail" DOTSIGN "hu", FALSE },
  { "László Horváth", "leslie" DOTSIGN "translate" ATSIGN "yahoo" DOTSIGN "co" DOTSIGN "uk", FALSE },
  { "Nagy Gábor", "jackson" DOTSIGN "gabor" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Indonesian */
static const TranslatorInfo xfce_translators_id[] =
{
  { "Andhika Padmawan", "andhika" DOTSIGN "padmawan" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ardjuna", "asyura" DOTSIGN "x" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Zaenal", "zaenal1234" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Icelandic */
static const TranslatorInfo xfce_translators_is[] =
{
  { "Kristófer Arnþórsson", "kristoferarnthors" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sveinn í Felli", "sveinki" ATSIGN "nett" DOTSIGN "is", FALSE },
  { "Theódór S. Andrésson", "husgafl" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Italian */
static const TranslatorInfo xfce_translators_it[] =
{
  { "Amigamagic", "debianmaverick" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Andreazube", "andreazuben" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Crazyaxe", "angerangel" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Cristian Marchi", "cri" DOTSIGN "penta" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Edoardo Maria Elidoro", "edoardo" DOTSIGN "elidoro" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Enrico Polesel", "polesel" ATSIGN "poisson" DOTSIGN "phc" DOTSIGN "unipi" DOTSIGN "it", FALSE },
  { "Francesco Groccia", "frgroccia" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Gianluca Foddis", "gianluca" DOTSIGN "foddis" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Leonardo Totaro", "elleti" DOTSIGN "brainvision" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Milozzy", "marco" DOTSIGN "sting" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Salvatorexfce", "salvatorexfce" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Winebar", "vs" DOTSIGN "winebar" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Japanese */
static const TranslatorInfo xfce_translators_ja[] =
{
  { "Hchenmisc", "hao" DOTSIGN "chen" DOTSIGN "jobs" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Masato Hashimoto", "hashimo" ATSIGN "xfce" DOTSIGN "org", FALSE },
  { "Nobuhiro Iwamatsu", "iwamatsu" ATSIGN "nigauri" DOTSIGN "org", FALSE },
  { NULL, NULL }
};


/* Kazakh */
static const TranslatorInfo xfce_translators_kk[] =
{
  { "Baurzhan Muftakhidinov", "baurthefirst" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Korean */
static const TranslatorInfo xfce_translators_ko[] =
{
  { "BAK Chan-Jin", "yeoulongg" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Jasonjang", "hl1sxa" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Kentarch", "bkrhlim" ATSIGN "aol" DOTSIGN "com", FALSE },
  { "Lego37yoon", "lego37yoon" ATSIGN "outlook" DOTSIGN "com", FALSE },
  { "Seong-ho Cho", "darkcircle" DOTSIGN "0426" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sungjin Gang", "potopro" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sung Jin Gang", "ujuc" ATSIGN "ujuc" DOTSIGN "kr", FALSE },
  { NULL, NULL }
};


/* Lithuanian */
static const TranslatorInfo xfce_translators_lt[] =
{
  { "Algimantas Margevičius", "margevicius" DOTSIGN "algimantas" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ričardas Vasiulis", "ricardas" DOTSIGN "v" ATSIGN "inbox" DOTSIGN "lt", FALSE },
  { NULL, NULL }
};


/* Latvian */
static const TranslatorInfo xfce_translators_lv[] =
{
  { "Gatis Kalniņš <> <Gatis Kalniņš", ">", FALSE },
  { "Rihards Prieditis", "rprieditis" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Malay */
static const TranslatorInfo xfce_translators_ms[] =
{
  { "Abuyop", "abuyop" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ceghap", "hello" ATSIGN "ceghap" DOTSIGN "com", FALSE },
  { "Mohd. Nadzrin Sapari", "terjemah" DOTSIGN "puretech" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Norwegian Bokmål */
static const TranslatorInfo xfce_translators_nb[] =
{
  { "Allan Nordhøy", "comradekingu" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Haarek", "haarektrans" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Kevin Brubeck Unhammer", "javkalas" ATSIGN "mm" DOTSIGN "st", FALSE },
  { "Papparonny", "ronny" ATSIGN "olufsen" DOTSIGN "org", FALSE },
  { "Takoi", "thomas" DOTSIGN "amland" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Terje Uriansrud", "terje" ATSIGN "uriansrud" DOTSIGN "net", FALSE },
  { NULL, NULL }
};


/* Dutch (Flemish) */
static const TranslatorInfo xfce_translators_nl[] =
{
  { "Auke Kok", "sofar" ATSIGN "foo-projects" DOTSIGN "org", FALSE },
  { "Nick Schermer", "nickschermer" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Pjotr Anon", "pliniusminor" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Pjotr Vertaalt", "pjotrvertaalt" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Timo Verbeek", "timoverbeek10" ATSIGN "hotmail" DOTSIGN "com", FALSE },
  { "Vincent Tunru", "projects" ATSIGN "vinnl" DOTSIGN "nl", FALSE },
  { NULL, NULL }
};


/* Norwegian Nynorsk */
static const TranslatorInfo xfce_translators_nn[] =
{
  { "Eivind Ødegård", "gingermig" ATSIGN "yahoo" DOTSIGN "no", FALSE },
  { "Kevin Brubeck Unhammer", "javkalas" ATSIGN "mm" DOTSIGN "st", FALSE },
  { NULL, NULL }
};


/* Occitan */
static const TranslatorInfo xfce_translators_oc[] =
{
  { "Cedric31", "cvalmary" ATSIGN "yahoo" DOTSIGN "fr", FALSE },
  { NULL, NULL }
};


/* Panjabi */
static const TranslatorInfo xfce_translators_pa[] =
{
  { "A S Alam", "apreet" DOTSIGN "alam" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Polish */
static const TranslatorInfo xfce_translators_pl[] =
{
  { "Adam Stachowicz", "saibamenppl" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Cyryl Sochacki", "cyrylsochacki" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Dawid", "hoek" ATSIGN "hoek" DOTSIGN "pl", FALSE },
  { "Elder", "elderlinx" ATSIGN "riseup" DOTSIGN "net", FALSE },
  { "Elzear", "babciaroziazpogwizdowa" ATSIGN "wp" DOTSIGN "pl", FALSE },
  { "Emanuel Borówko", "trzynastak" ATSIGN "o2" DOTSIGN "pl", FALSE },
  { "Ireneusz Gierlach", "irek" DOTSIGN "gierlach" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Jakub Waśko", "javazlaz" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Kamil Polczak", "elderlinx" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Marcin Romańczuk", "abjsyn" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Michał Jeż", "michal" DOTSIGN "je2u" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Michał Olber", "michal" DOTSIGN "olber" ATSIGN "osworld" DOTSIGN "pl", FALSE },
  { "Pawel10", "pawelklimek102" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Piotr Sokół", "psokol" ATSIGN "jabster" DOTSIGN "pl", FALSE },
  { "Piotr Strębski", "strebski" ATSIGN "o2" DOTSIGN "pl", FALSE },
  { "Tomasz Chudyk", "chudyk" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Portuguese */
static const TranslatorInfo xfce_translators_pt[] =
{
  { "Alexandre Fidalgo", "alexandremagnos15" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Nuno Miguel", "nunomgue" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sérgio Marques", "smarquespt" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Portuguese (Brazilian) */
static const TranslatorInfo xfce_translators_pt_BR[] =
{
  { "André Miranda", "andreldm1989" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Cleber de Souza Corrêa", "cscorrea" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Enrico Nicoletto", "enrico" DOTSIGN "br" ATSIGN "gmx" DOTSIGN "co" DOTSIGN "uk", FALSE },
  { "Henrique P. Machado", "zehrique" ATSIGN "xfce" DOTSIGN "org", FALSE },
  { "Joelso Andrade", "kosmofilo" ATSIGN "ymail" DOTSIGN "com", FALSE },
  { "Michael Martins", "michaelfm21" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Miguel Frasson", "mvsfrasson" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Mtobias", "marcelo" DOTSIGN "tobbias" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Neliton Pereira Junior", "nelitonpjr" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Og Maciel", "ogmaciel" ATSIGN "gnome" DOTSIGN "org", FALSE },
  { "Rafael Ferreira", "rafael" DOTSIGN "f" DOTSIGN "f1" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Rafael Neri", "rafepel" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sérgio Cipolla", "secipolla" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Tomas Schertel", "tschertel" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Victor Gonçalves", "hotcyv" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Vladimir Melo", "vladimirmelo" DOTSIGN "psi" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Romanian */
static const TranslatorInfo xfce_translators_ro[] =
{
  { "Mișu Moldovan", "dumol" ATSIGN "xfce" DOTSIGN "org", FALSE },
  { "Strainu", "xfce" ATSIGN "strainu" DOTSIGN "ro", FALSE },
  { NULL, NULL }
};


/* Russian */
static const TranslatorInfo xfce_translators_ru[] =
{
  { "026rus", "026rus" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "AK", "ak099" ATSIGN "mail" DOTSIGN "ru", FALSE },
  { "Aleksandr Ponomarenko", "davian818" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Aleksandr Sorokin", "equusa" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "AlexanderFilev", "ifillrok" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Alexander Matveyev", "a" DOTSIGN "s" DOTSIGN "matveyev" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Alexandr Boltris", "ua2fgb" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Alexey Batiuk", "alexey" DOTSIGN "batiuk" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Alex Z", "ad_user" ATSIGN "lavabit" DOTSIGN "com", FALSE },
  { "Andres Kovtunos", "kovtunos" ATSIGN "yandex" DOTSIGN "ru", FALSE },
  { "Andrey Ivankov", "andrey" DOTSIGN "ivankov" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Artem Zolochevskiy", "artem" DOTSIGN "zolochevskiy" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Brdassign", "dmitriy" DOTSIGN "borodiy" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Claque", "cpt-alatriste" ATSIGN "ya" DOTSIGN "ru", FALSE },
  { "Denis Koryavov", "dkoryavov" ATSIGN "yandex" DOTSIGN "ru", FALSE },
  { "Dmitrij Smirnov", "arch" ATSIGN "cnc-parts" DOTSIGN "info", FALSE },
  { "Dmitriy Kudryashov", "overmailed" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Kyrill Detinov", "lazy" DOTSIGN "kent" ATSIGN "opensuse" DOTSIGN "org", FALSE },
  { "Lowrider", "pams" ATSIGN "imail" DOTSIGN "ru", FALSE },
  { "Roman K", "mrdoctorwho" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sergey Alyoshin", "alyoshin" DOTSIGN "s" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sergey Shlyapugin", "shlyapugin" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Someniatko", "someniatko" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Styopa Semenukha", "semenukha" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Velisarus", "velisarus" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Vlad Vasilev", "lortwer" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Sinhala */
static const TranslatorInfo xfce_translators_si[] =
{
  { "Akila Wajirasena", "akila" DOTSIGN "wajirasena" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Anandawardhana", "anandawardhana" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Danishka Navin", "danishka" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Kalpa Pathum Welivitigoda", "callkalpa" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Kasundigital", "kasunindika" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Kpgtharaka", "kpgtharaka" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Prabath Galagamage", "gprabath" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Slovak */
static const TranslatorInfo xfce_translators_sk[] =
{
  { "Marek Hlava", "headsvk" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Michal Löffler", "lofflermichalloffler" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Peter Bubelíny", "p" DOTSIGN "bubeliny" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Robert Hartl", "hartl" DOTSIGN "robert" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Slavko", "linux" ATSIGN "slavino" DOTSIGN "sk", FALSE },
  { "Tomáš Vadina", "kyberdev" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Slovenian */
static const TranslatorInfo xfce_translators_sl[] =
{
  { "Ansich", "mojmejlzaforume" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Anthonmanix", "anthon" DOTSIGN "manix" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Dražen M", "drazen" ATSIGN "ubuntu" DOTSIGN "si", FALSE },
  { "Gašper Tomažič", "gasper" ATSIGN "gmx" DOTSIGN "com", FALSE },
  { "Holden87", "latinovic87" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Klemen Košir", "klemen913" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Nenad Latinović", "nenadlatinovic" ATSIGN "lavabit" DOTSIGN "com", FALSE },
  { "Rok Kepa", "rokkepa" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sasa Batistic", "sasa" DOTSIGN "batistic" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Uros Preloznik", "uros00" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Albanian */
static const TranslatorInfo xfce_translators_sq[] =
{
  { "Ard1t", "ardit" DOTSIGN "dani" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Besnik Bleta", "besnik" ATSIGN "programeshqip" DOTSIGN "org", FALSE },
  { "Erlin Hysenbelliu", "erlinh91" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Serbian */
static const TranslatorInfo xfce_translators_sr[] =
{
  { "Мирослав Николић", "miroslavnikolic" ATSIGN "rocketmail" DOTSIGN "com", FALSE },
  { "Саша Петровић", "salepetronije" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Harald Judt", "h" DOTSIGN "judt" ATSIGN "gmx" DOTSIGN "at", FALSE },
  { "Mpopovic", "gpopac" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Swedish */
static const TranslatorInfo xfce_translators_sv[] =
{
  { "Alex Nordlund", "deep" DOTSIGN "alexander" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Bittin", "cs_bittin" ATSIGN "msn" DOTSIGN "com", FALSE },
  { "Daniel Nylander", "po" ATSIGN "danielnylander" DOTSIGN "se", FALSE },
  { "Elefterios Lundell", "winnie666" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "FredN", "fredrik" ATSIGN "nyqvist" DOTSIGN "biz", FALSE },
  { "Kim Svensson", "ks6g10" ATSIGN "soton" DOTSIGN "ac" DOTSIGN "uk", FALSE },
  { "PavelNicklasson", "pavelnicklasson" ATSIGN "bahnhof" DOTSIGN "se", FALSE },
  { "Peterdenk", "peter" ATSIGN "skypay" DOTSIGN "se", FALSE },
  { "Rickard Larsson", "larsson" ATSIGN "odus" DOTSIGN "se", FALSE },
  { NULL, NULL }
};


/* Telugu */
static const TranslatorInfo xfce_translators_te[] =
{
  { "వీవెన్", "veeven" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "ప్రవీణ్ ఇళ్ళ", "mail2ipn" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Thai */
static const TranslatorInfo xfce_translators_th[] =
{
  { "Theppitak Karoonboonyanan", "theppitak" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Turkish */
static const TranslatorInfo xfce_translators_tr[] =
{
  { "Akın Ömeroğlu", "akin" ATSIGN "pardus" DOTSIGN "org" DOTSIGN "tr", FALSE },
  { "Ali Polatel", "ali" DOTSIGN "polatel" ATSIGN "ozguryazilim" DOTSIGN "com" DOTSIGN "tr", FALSE },
  { "Alper Tekinalp", "alper" DOTSIGN "tekinalp" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Askar05", "asirkaraman" ATSIGN "yahoo" DOTSIGN "de", FALSE },
  { "Aybuke", "aybuke" DOTSIGN "147" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Aydan Taşdemir", "aydantasdemir" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ayhan YALÇINSOY", "ayhanyalcinsoy" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Caner Gural", "cgural" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ertuğrul HAZAR", "ertugrulhazar" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Farukuzun", "farukuzun" ATSIGN "mail" DOTSIGN "com", FALSE },
  { "Fatih Erdem", "93" DOTSIGN "fatiherdem" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Gökhan Kılınç", "kilincgokhan" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Gökmen Görgen", "gkmngrgn" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ilker Dagli", "ilker" ATSIGN "ilkerdagli" DOTSIGN "info", FALSE },
  { "Martinamca", "martinamca" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Mustafa Tekkoyun", "mustafa" DOTSIGN "tekkoyun" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Natavan Mirzayeva", "mirzayevanatavan" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Necdet Yücel", "necdetyucel" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Osman Karagöz", "osmank3" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Samed Beyribey", "beyribey" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Server Acim", "serveracim" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Utku Aydın", "utkuaydin" ATSIGN "archlinux" DOTSIGN "org" DOTSIGN "tr", FALSE },
  { "Utku Berberoğlu", "utku" DOTSIGN "berber" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Volkangezer", "volkangezer" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Yakup", "mutouk" ATSIGN "yandex" DOTSIGN "ru", FALSE },
  { "Zafer Eren", "zaferern" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Zeki", "zeki" DOTSIGN "ozguryazilim" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Özgür Kuru", "ozgur" ATSIGN "ozgurkuru" DOTSIGN "net", FALSE },
  { NULL, NULL }
};


/* Uyghur */
static const TranslatorInfo xfce_translators_ug[] =
{
  { "Abduqadir Abliz", "sahran" DOTSIGN "ug" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Gheyret Kenji", "gheyret" ATSIGN "yahoo" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Ukrainian */
static const TranslatorInfo xfce_translators_uk[] =
{
  { "Andriy Matkovsky", "sidius" DOTSIGN "ua" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Dmitry Nikitin", "luckas_fb" ATSIGN "mail" DOTSIGN "ru", FALSE },
  { "Oleksandr Natalenko", "pfactum" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Olexandr Nesterenko", "olexn" ATSIGN "ukr" DOTSIGN "net", FALSE },
  { "Pavlo Bilyak", "jpavlo11" ATSIGN "ukr" DOTSIGN "net", FALSE },
  { "Yarema aka Knedlyk", "yupadmin" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Zubr139", "zubr139" ATSIGN "ukr" DOTSIGN "net", FALSE },
  { NULL, NULL }
};


/* Uzbek */
static const TranslatorInfo xfce_translators_uz[] =
{
  { "Umidjon Almasov", "u" DOTSIGN "almasov" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Vietnamese */
static const TranslatorInfo xfce_translators_vi[] =
{
  { "Crziter", "crziter" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Duy Truong Nguyen", "truongap" DOTSIGN "ars" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ppanhh", "ppanhh" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Vinh Nguyen", "kureikain" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Chinese (China) */
static const TranslatorInfo xfce_translators_zh_CN[] =
{
  { "Chipong Luo", "chipong" DOTSIGN "luo" ATSIGN "yahoo" DOTSIGN "com", FALSE },
  { "Greensea", "gs" ATSIGN "bbxy" DOTSIGN "net", FALSE },
  { "Hunt Xu", "mhuntxu" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Qianqian Fang", "fangqq" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Xianhao", "qinghao1" ATSIGN "foxmail" DOTSIGN "com", FALSE },
  { "玉堂白鹤", "yjwork" ATSIGN "qq" DOTSIGN "com", FALSE },
  { "周潇波", "zhouxiaobo" DOTSIGN "500" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "白铭骢", "jeffbaichina" ATSIGN "members" DOTSIGN "fsf" DOTSIGN "org", FALSE },
  { NULL, NULL }
};


/* Chinese (Hong Kong) */
static const TranslatorInfo xfce_translators_zh_HK[] =
{
  { "Walter Cheuk", "wwycheuk" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "文豪 卫", "waimanho2765galois" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* Chinese (Taiwan) */
static const TranslatorInfo xfce_translators_zh_TW[] =
{
  { "Cheng-Chia Tseng", "pswo10680" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Chia-Han Lee", "gloomysaga" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ethan42411", "jrpropo10282003" ATSIGN "yahoo" DOTSIGN "com" DOTSIGN "tw", FALSE },
  { "Jeff Huang", "s8321414" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Pei Yi Chen", "cpyimail" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Ruei-Yuan Lu", "rueiyuan" DOTSIGN "lu" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Sofyalai", "sofyalai" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { "Walter Cheuk", "wwycheuk" ATSIGN "gmail" DOTSIGN "com", FALSE },
  { NULL, NULL }
};


/* teams list, sorted alphabetically by language name */
static const TranslatorTeam xfce_translators[] =
{
  { "Albanian", "sq", xfce_translators_sq },
  { "Amharic", "am", xfce_translators_am },
  { "Arabic", "ar", xfce_translators_ar },
  { "Asturian", "ast", xfce_translators_ast },
  { "Basque", "eu", xfce_translators_eu },
  { "Belarusian", "be", xfce_translators_be },
  { "Bengali", "bn", xfce_translators_bn },
  { "Bulgarian", "bg", xfce_translators_bg },
  { "Catalan", "ca", xfce_translators_ca },
  { "Chinese (China)", "zh_CN", xfce_translators_zh_CN },
  { "Chinese (Hong Kong)", "zh_HK", xfce_translators_zh_HK },
  { "Chinese (Taiwan)", "zh_TW", xfce_translators_zh_TW },
  { "Croatian", "hr", xfce_translators_hr },
  { "Czech", "cs", xfce_translators_cs },
  { "Danish", "da", xfce_translators_da },
  { "Dutch (Flemish)", "nl", xfce_translators_nl },
  { "English (Australia)", "en_AU", xfce_translators_en_AU },
  { "English (Great Britain)", "en_GB", xfce_translators_en_GB },
  { "Esperanto", "eo", xfce_translators_eo },
  { "Estonian", "et", xfce_translators_et },
  { "Finnish", "fi", xfce_translators_fi },
  { "French", "fr", xfce_translators_fr },
  { "Galician", "gl", xfce_translators_gl },
  { "German", "de", xfce_translators_de },
  { "Greek", "el", xfce_translators_el },
  { "Hebrew", "he", xfce_translators_he },
  { "Hungarian", "hu", xfce_translators_hu },
  { "Icelandic", "is", xfce_translators_is },
  { "Indonesian", "id", xfce_translators_id },
  { "Italian", "it", xfce_translators_it },
  { "Japanese", "ja", xfce_translators_ja },
  { "Kazakh", "kk", xfce_translators_kk },
  { "Korean", "ko", xfce_translators_ko },
  { "Latvian", "lv", xfce_translators_lv },
  { "Lithuanian", "lt", xfce_translators_lt },
  { "Malay", "ms", xfce_translators_ms },
  { "Norwegian Bokmål", "nb", xfce_translators_nb },
  { "Norwegian Nynorsk", "nn", xfce_translators_nn },
  { "Occitan", "oc", xfce_translators_oc },
  { "Panjabi", "pa", xfce_translators_pa },
  { "Persian", "fa", xfce_translators_fa },
  { "Polish", "pl", xfce_translators_pl },
  { "Portuguese", "pt", xfce_translators_pt },
  { "Portuguese (Brazilian)", "pt_BR", xfce_translators_pt_BR },
  { "Romanian", "ro", xfce_translators_ro },
  { "Russian", "ru", xfce_translators_ru },
  { "Serbian", "sr", xfce_translators_sr },
  { "Sinhala", "si", xfce_translators_si },
  { "Slovak", "sk", xfce_translators_sk },
  { "Slovenian", "sl", xfce_translators_sl },
  { "Spanish", "es", xfce_translators_es },
  { "Swedish", "sv", xfce_translators_sv },
  { "Telugu", "te", xfce_translators_te },
  { "Thai", "th", xfce_translators_th },
  { "Turkish", "tr", xfce_translators_tr },
  { "Ukrainian", "uk", xfce_translators_uk },
  { "Uyghur", "ug", xfce_translators_ug },
  { "Uzbek", "uz", xfce_translators_uz },
  { "Vietnamese", "vi", xfce_translators_vi },
};
