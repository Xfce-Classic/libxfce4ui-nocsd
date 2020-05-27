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

static const TranslatorInfo xfce_translators_am[] =
{
	{ "samson","sambelet@yahoo.com", FALSE },
	{ "T Tefera","tefera.tegegne@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ar[] =
{
	{ "Hayder Majid","cteehayder@gmail.com", FALSE },
	{ "mohammad alhargan","malham1@hotmail.com", FALSE },
	{ "Oukiki Saleh","salehoukiki@gmail.com", FALSE },
	{ "عبدالله رضوان","abbodmar@gmail.com", FALSE },
	{ "كريم أولاد الشلحة","herr.linux88@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ast[] =
{
	{ "enolp","enolp@softastur.org", FALSE },
	{ "Ḷḷumex03","tornes@opmbx.org", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_be[] =
{
	{ "zmicer turok","zmicerturok@gmail.com", FALSE },
	{ "Сяргей Снапкоўскі","sirozass@outlook.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_bg[] =
{
	{ "Georgi Georgiev","georgiev_1994@abv.bg", FALSE },
	{ "Ivailo Panamski","ipanamski@gmail.com", FALSE },
	{ "Kiril Kirilov","cybercop_montana@abv.bg", FALSE },
	{ "Красимир Беров","k.berov@gmail.com", FALSE },
	{ "Любомир Василев","lyubomirv@abv.bg", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_bn[] =
{
	{ "Ashraful Islam","rediancool@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ca[] =
{
	{ "Adrián Laviós","registres@lavios.cat", FALSE },
	{ "Alberto Sánchez Molero","alsamolero@gmail.com", FALSE },
	{ "Carles Muñoz Gorriz","carlesmu@internautas.org", FALSE },
	{ "Davidmp","medipas@gmail.com", FALSE },
	{ "Robert Antoni Buj Gelonch","rbuj@fedoraproject.org", FALSE },
	{ "Roger Pueyo Centelles","transifex@rogerpueyo.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_cs[] =
{
	{ "Alois Nešpor","info@aloisnespor.info", FALSE },
	{ "Daniel Kubat","dan.kubat@gmail.com", FALSE },
	{ "Michal Várady","miko.vaji@gmail.com", FALSE },
	{ "Pavel Borecki","pavel.borecki@gmail.com", FALSE },
	{ "Petr Šimáček","petr.simacek@gmail.com", FALSE },
	{ "Tomas Brabenec","tomas@brabenec.net", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_cy[] =
{
    { "Geraint Rowlands","ansbaradigeidfran@gmail.com", FALSE },
    { NULL, NULL }
};
static const TranslatorInfo xfce_translators_da[] =
{
	{ "Aputsiak Niels Janussen (Skjalden)","aj@isit.gl", FALSE },
	{ "Chris Darnell","chris@cedeel.com", FALSE },
	{ "Linuxbruger","y.z@live.dk", FALSE },
	{ "Morten Juhl-Johansen Zölde-Fejér","morten@writtenandread.net", FALSE },
	{ "scootergrisen","scootergrisen@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_de[] =
{
	{ "Andreas Eitel","github-aneitel@online.de", FALSE },
	{ "Georg Eckert","eckert.georg@gmx.de", FALSE },
	{ "Harald Judt","h.judt@gmx.at", FALSE },
	{ "Johannes Lips","johannes.lips@gmail.com", FALSE },
	{ "Oliver Burkardt","oliver.burkardt@gmail.com", FALSE },
	{ "Simon Steinbeiß","simon.steinbeiss@gmail.com", FALSE },
	{ "Tobias Bannert","tobannert@gmail.com", FALSE },
	{ "Vinzenz Vietzke","vinz@vinzv.de", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_el[] =
{
	{ "Apóstolos Papaðimitríu","apostolos.papadimitriu@gmail.com", FALSE },
	{ "Christos Arvanitis","arvchristos@gmail.com", FALSE },
	{ "Efstathios Iosifidis","iefstathios@gmail.com", FALSE },
	{ "Georgios Zarkadas","georgios.zarkadas@gmail.com", FALSE },
	{ "Panagiotis Mantzios","pmantzios@hotmail.com", FALSE },
	{ "Panagiotis Tabakis","tabakisp@gmail.com", FALSE },
	{ "Petros Alexandrinos","lipsari@yahoo.com", FALSE },
	{ "Spiros Georgaras","sng@hellug.gr", FALSE },
	{ "Πέτρος Σαμαράς","psamaras1@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_en_AU[] =
{
	{ "John Humphrys","john.humphrys@pm.me", FALSE },
	{ "Michael Findlay","translate@cobber-linux.org", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_en_CA[] =
{
	{ "Steve Harris","steve@cultureofweb.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_en_GB[] =
{
	{ "Andi Chandler","andi@gowling.com", FALSE },
	{ "Jackson Doak","noskcaj@ubuntu.com", FALSE },
	{ "Robert Readman","robert_readman@hotmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_eo[] =
{
	{ "Iris Ilexiris","iris.ilexiris@gmail.com", FALSE },
	{ "Mike Wortin","mikewortin@gmail.com", FALSE },
	{ "Robin van der Vliet","info@robinvandervliet.nl", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_es[] =
{
	{ "Alfredo Quintero","alfredomob@gmail.com", FALSE },
	{ "Brian Peraza-Orozco","brian.peraza@gmail.com", FALSE },
	{ "César Enrique García","cquike@gmail.com", FALSE },
	{ "Christian Manuel Torres Romero","christian.mtr@gmail.com", FALSE },
	{ "Francisco F. Serrador","serrador@tecknolabs.com", FALSE },
	{ "Francisco Serrador","serrador@tecknolabs.com", FALSE },
	{ "gabrieltandil","gabriel.tandil@gmail.com", FALSE },
	{ "Javier F. Serrador","serrador@tecknolabs.com", FALSE },
	{ "Juan José Fernández Monreal","juanjofaico22@gmail.com", FALSE },
	{ "Luis Mendoza","darcn181@gmail.com", FALSE },
	{ "Manolo Díaz","diaz.manolo@gmail.com", FALSE },
	{ "Pablo Lezaeta Reyes [pˈaβ̞lo lˌe̞θaˈeta rˈejɛ]","prflr88@gmail.com", FALSE },
	{ "Sergio García","oigres200@gmail.com", FALSE },
	{ "wakutiteo","wakutiteo@protonmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_et[] =
{
	{ "Mattias Põldaru","mahfiaz@gmail.com", FALSE },
	{ "vaba","vaba@riseup.net", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_eu[] =
{
	{ "Aitor Beriain","beriain@bitmessage.ch", FALSE },
	{ "Asier Iturralde Sarasola","asier.iturralde@gmail.com", FALSE },
	{ "beriain","beriain@bitmessage.ch", FALSE },
	{ "Egoitz Rodriguez Obieta","egoitzro@gmail.com", FALSE },
	{ "Piarres Beobide","pi@beobide.net", FALSE },
	{ "Sr Aldeano","sraldeano@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_fa_IR[] =
{
	{ "Ali Molaei","ali.molaei@protonmail.com", FALSE },
	{ "Ali Vakilzade","ali.vakilzade@gmail.com", FALSE },
	{ "Arash Kadkhodaei","slasharash@protonmail.com", FALSE },
	{ "iman salmani","i.salmani13802000@gmail.com", FALSE },
	{ "ramin.najarbashi","ramin.najarbashi@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_fi[] =
{
	{ "Jiri Grönroos","jiri.gronroos@iki.fi", FALSE },
	{ "Juhani Numminen","juhaninumminen0@gmail.com", FALSE },
	{ "Lasse Liehu","larso@gmx.com", FALSE },
	{ "Pasi Lallinaho","pasi@shimmerproject.org", FALSE },
	{ "Tapio Väisänen","tapio.vaeisaenen@gmail.com", FALSE },
	{ "Tero Mononen","tero@mononen.eu", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_fr[] =
{
	{ "Charles Monzat","c.monzat@laposte.net", FALSE },
	{ "Guillaume Laville","laville.guillaume@gmail.com", FALSE },
	{ "HANNEQUIN Lionel","ifsilr1@free.fr", FALSE },
	{ "jc1","jc1.quebecos@gmail.com", FALSE },
	{ "Ldm Public","ldmpub@gmail.com", FALSE },
	{ "Maxime Bonillo","maxime@bonillo.org", FALSE },
	{ "nodiscc","nodiscc@gmail.com", FALSE },
	{ "Pierre-Adrien Carton","pierre.adrien.carton@gmail.com", FALSE },
	{ "Remi Andruccioli","remi.andruccioli@gmail.com", FALSE },
	{ "Silvère Latchurié","slatchurie@gmail.com", FALSE },
	{ "Urien Desterres","urien.desterres@gmail.com", FALSE },
	{ "Yannick Le Guen","leguen.yannick@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_gl[] =
{
	{ "Daniel Muñiz Fontoira","dani@damufo.com", FALSE },
	{ "Leandro Regueiro","leandro.regueiro@gmail.com", FALSE },
	{ "Xosé","xosecalvo@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_he[] =
{
	{ "Bar Boko","bokodev@outlook.com", FALSE },
	{ "Elishai Eliyahu","e1907@mm.st", FALSE },
	{ "GenghisKhan","genghiskhan@gmx.ca", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_hr[] =
{
	{ "Edin Veskovic","edin.lockedin@gmail.com", FALSE },
	{ "Ivica  Kolić","ikoli@yahoo.com", FALSE },
	{ "Lovro Kudelić","lovro.kudelic@outlook.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_hu[] =
{
	{ "Balázs Meskó","meskobalazs@gmail.com", FALSE },
	{ "Balázs Úr","urbalazs@gmail.com", FALSE },
	{ "Benedek Imre","nucleo@indamail.hu", FALSE },
	{ "gyeben","gyonkibendeguz@gmail.com", FALSE },
	{ "kelemeng","kelemeng@ubuntu.com", FALSE },
	{ "Nagy Gábor","jackson.gabor@gmail.com", FALSE },
	{ "user14","nleknh@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_id[] =
{
	{ "Andhika Padmawan","andhika.padmawan@gmail.com", FALSE },
	{ "Anton Toni Agung","vdrive6@gmail.com", FALSE },
	{ "Ardjuna","Asyura.x@gmail.com", FALSE },
	{ "Kukuh Syafaat","syafaatkukuh@gmail.com", FALSE },
	{ "Taufik Mulyana","taufik@nothinux.id", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_is[] =
{
	{ "Kristján Magnússon","kristjanmagnus@gmail.com", FALSE },
	{ "Sveinn í Felli","sv1@fellsnet.is", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_it[] =
{
	{ "bebabi34","bebabi34@email.it", FALSE },
	{ "Cristian Marchi","cri.penta@gmail.com", FALSE },
	{ "Davide Truffa","davide.truffa@gmail.com", FALSE },
	{ "Edoardo Maria Elidoro","edoardo.elidoro@gmail.com", FALSE },
	{ "Emanuele Petriglia","inbox@emanuelepetriglia.me", FALSE },
	{ "Enrico","allin@infinito.it", FALSE },
	{ "Enrico B.","enricobe@hotmail.com", FALSE },
	{ "Francesco Galizzi","f.galizzi92@gmail.com", FALSE },
	{ "idetao","marcxosm@gmail.com", FALSE },
	{ "Mark","marco_pace@msn.com", FALSE },
	{ "Massimiliano Vessi","angerangel@gmail.com", FALSE },
	{ "oblo","oblomov78@hotmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ja[] =
{
	{ "Masato HASHIMOTO","cabezon.hashimoto@gmail.com", FALSE },
	{ "Nobuhiro Iwamatsu","iwamatsu@nigauri.org", FALSE },
	{ "出口　憲","kdeguchi@sz.tokoha-u.ac.jp", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_kk[] =
{
	{ "Baurzhan Muftakhidinov","baurthefirst@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_kn[] =
{
	{ "Rizma Banu","Rizmarijju@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ko[] =
{
	{ "Cybertramp","paran_son@outlook.com", FALSE },
	{ "Seong-ho Cho","darkcircle.0426@gmail.com", FALSE },
	{ "Sungjin Kang","potopro@gmail.com", FALSE },
	{ "박정규(Jung-Kyu Park)","bagjunggyu@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_lt[] =
{
	{ "Moo","moose@mail.ru", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_lv[] =
{
	{ "Gatis Kalniņš","", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ms[] =
{
	{ "abuyop","abuyop@gmail.com", FALSE },
	{ "Puretech","terjemah.puretech@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_nb[] =
{
	{ "Allan Nordhøy","epost@anotheragency.no", FALSE },
	{ "Åsmund Berg Holm","berg.holm@outlook.com", FALSE },
	{ "Eirik Dekko","edekko@gmail.com", FALSE },
	{ "Erlend Østlie","erlendandreas12368@gmail.com", FALSE },
	{ "Harald H.","haarektrans@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_nl[] =
{
	{ "dragnadh","dragnadh@gmail.com", FALSE },
	{ "Pjotr","pjotrvertaalt@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_nn[] =
{
	{ "Håvard Krogstie","krogstie.havard@gmail.com", FALSE },
	{ "Kevin Brubeck Unhammer","unhammer+dill@mm.st", FALSE },
	{ "Øystein Alværvik","internett@protonmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_oc[] =
{
	{ "Cédric Valmary","cvalmary@yahoo.fr", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_pa[] =
{
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_pl[] =
{
	{ "Dominik Wojnar","dominik.wojnar@gmail.com", FALSE },
	{ "G G","grzegorz.gebczynski@gmail.com", FALSE },
	{ "Hoek","dawid.job@gmail.com", FALSE },
	{ "Kamil elder P.","elderlinx@riseup.net", FALSE },
	{ "Marcin Mikołajczak","me@m4sk.in", FALSE },
	{ "Marcin Nawrocki","shinoksik@gmail.com", FALSE },
	{ "Michał Olber","michal@olber.pl", FALSE },
	{ "No Ne","mrerexx@gmail.com", FALSE },
	{ "Piotr Sokół","psokol.l10n@gmail.com", FALSE },
	{ "Piotr Strębski","strebski@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_pt[] =
{
	{ "Alexandre Fidalgo","alexandremagnos15@gmail.com", FALSE },
	{ "Bruno Guerreiro","american.jesus.pt@gmail.com", FALSE },
	{ "José Vieira","jvieira33@sapo.pt", FALSE },
	{ "Nuno Miguel","nunomgue@gmail.com", FALSE },
	{ "Rui","xymarior@yandex.com", FALSE },
	{ "Sérgio Marques","smarquespt@gmail.com", FALSE },
	{ "Hugo Carvalho","hugokarvalho@hotmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_pt_BR[] =
{
	{ "André Miranda","andre42m@gmail.com", FALSE },
	{ "Luis Borges","roninborges@gmail.com", FALSE },
	{ "Marcelo Tobias","marcelo.tobbias@gmail.com", FALSE },
	{ "Michael Martins","michaelfm21@gmail.com", FALSE },
	{ "Miguel V. S. Frasson","mvsfrasson@gmail.com", FALSE },
	{ "Otavio Augusto Gomes","gmsotavio@gmail.com", FALSE },
	{ "Rafael Fontenelle","rffontenelle@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ro[] =
{
	{ "Gaman Gabriel","gamgabriel25@gmail.com", FALSE },
	{ "Mișu Moldovan","dumol@l10n.ro", FALSE },
	{ "vyper","xvirusxx@gmail.com", FALSE },
	{ "Yupy","yupy_17y@yahoo.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ru[] =
{
	{ "Aleksandr P","davian818@gmail.com", FALSE },
	{ "AlexanderFilev","ifillrok@gmail.com", FALSE },
	{ "Alexey Nagornyak","tezaurismosis@gmail.com", FALSE },
	{ "Igor","f2404@yandex.ru", FALSE },
	{ "Lowrider","pams@imail.ru", FALSE },
	{ "Sergey Alyoshin","alyoshin.s@gmail.com", FALSE },
	{ "Velisarus","velisarus@gmail.com", FALSE },
	{ "Viktor Odintsev","ninetls@xfce.org", FALSE },
	{ "Александр","avfill@outlook.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_si[] =
{
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_sk[] =
{
	{ "asaas","lofflermichalloffler@gmail.com", FALSE },
	{ "Dušan Kazik","prescott66@gmail.com", FALSE },
	{ "Jose Riha","jose1711@gmail.com", FALSE },
	{ "kozec","kozec2@kozec.com", FALSE },
	{ "Michal Pirchala","michal.pirchala@gmail.com", FALSE },
	{ "Slavko","linux@slavino.sk", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_sl[] =
{
	{ "Aljoša Žagar","anthon.manix@gmail.com", FALSE },
	{ "ansich","mojmejlzaforume@gmail.com", FALSE },
	{ "Klemen Košir","klemen.kosir@kream.io", FALSE },
	{ "Nenad Latinović","latinovic87@gmail.com", FALSE },
	{ "ツ Kernc","kerncece@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_sq[] =
{
	{ "Arianit Kukaj","akukaj@msn.com", FALSE },
	{ "Besnik","besnik@programeshqip.org", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_sr[] =
{
	{ "Nikola Radovanović","cobisimo@gmail.com", FALSE },
	{ "Саша Петровић","salepetronije@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_sv[] =
{
	{ "Arve Eriksson","031299870@telia.com", FALSE },
	{ "Martin Stenröse","martin.stenrose@gmail.com", FALSE },
	{ "Påvel Nicklasson","pavel2@frimix.se", FALSE },
	{ "Stefan Höök","stefan.hook@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_te[] =
{
	{ "ప్రవీణ్ ఇళ్ళ","mail2ipn@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_th[] =
{
	{ "Theppitak Karoonboonyanan","theppitak@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_tr[] =
{
	{ "Ali Polatel","ali.polatel@ozguryazilim.com.tr", FALSE },
	{ "Butterfly","gokhanlnx@gmail.com", FALSE },
	{ "Demiray Muhterem","mdemiray@msn.com", FALSE },
	{ "Emin Tufan","etcetin@gmail.com", FALSE },
	{ "Kaan Bodur","kaanbodur@gmail.com", FALSE },
	{ "Muhammet Kara","muhammetk@gmail.com", FALSE },
	{ "Mustafa TEKKOYUN","inactive+tekotek@transifex.com", FALSE },
	{ "Natavan Mirzayeva","mirzayevanatavan@gmail.com", FALSE },
	{ "Necdet Yücel","necdetyucel@gmail.com", FALSE },
	{ "Volkan Gezer","volkangezer@gmail.com", FALSE },
	{ "zeki","zeki.ozguryazilim@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ug[] =
{
	{ "Abduqadir Abliz","sahran.ug@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_uk[] =
{
	{ "dsafsadf","heneral@gmail.com", FALSE },
	{ "Yarema aka Knedlyk","yupadmin@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ur[] =
{
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_ur_PK[] =
{
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_uz[] =
{
	{ "Umidjon Almasov","u.almasov@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_vi[] =
{
	{ "Duy Truong Nguyen","truongap.ars@gmail.com", FALSE },
	{ "Nguyên Bình","crziter@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_zh_CN[] =
{
	{ "Chipong Luo","chipong.luo@yahoo.com", FALSE },
	{ "dull2wall","ovrlanebel@tutanota.de", FALSE },
	{ "Hunt Xu","mhuntxu@gmail.com", FALSE },
	{ "Levi Zhou","congzhou821@gmail.com", FALSE },
	{ "Mingcong Bai","jeffbai@aosc.xyz", FALSE },
	{ "No Body","nemolus@gmail.com", FALSE },
	{ "SamHX","samzh@outlook.com", FALSE },
	{ "Shun","shun98@139.com", FALSE },
	{ "winjeg","winjeg@qq.com", FALSE },
	{ "wwj402","wwj402@gmail.com", FALSE },
	{ "xiaobo zhou","zhouxiaobo.500@gmail.com", FALSE },
	{ "周潇波","zhouxiaobo.500@gmail.com", FALSE },
	{ "张诚","xxzhangcheng1@gmail.com", FALSE },
	{ "浩翔 赵","1637979429@qq.com", FALSE },
	{ "玉堂白鹤","yjwork@qq.com", FALSE },
	{ "白铭骢","jeffbai@aosc.xyz", FALSE },
	{ "白铭骢","jeffbaichina@members.fsf.org", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_zh_HK[] =
{
	{ "Walter Cheuk","wwycheuk@gmail.com", FALSE },
	{ NULL, NULL }
};
static const TranslatorInfo xfce_translators_zh_TW[] =
{
	{ "byStarTW (pan93412)","pan93412@gmail.com", FALSE },
	{ "Cheng-Chia Tseng","pswo10680@gmail.com", FALSE },
	{ "Hsiu-Ming Chang","cges30901@gmail.com", FALSE },
	{ "Jeff Huang","s8321414@gmail.com", FALSE },
	{ "Walter Cheuk","wwycheuk@gmail.com", FALSE },
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
  { "English (Canada)", "en_CA", xfce_translators_en_CA },
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
  { "Kannada", "kn", xfce_translators_kn },
  { "Kazakh", "kk", xfce_translators_kk },
  { "Korean", "ko", xfce_translators_ko },
  { "Latvian", "lv", xfce_translators_lv },
  { "Lithuanian", "lt", xfce_translators_lt },
  { "Malay", "ms", xfce_translators_ms },
  { "Norwegian Bokmål", "nb", xfce_translators_nb },
  { "Norwegian Nynorsk", "nn", xfce_translators_nn },
  { "Occitan", "oc", xfce_translators_oc },
  { "Panjabi", "pa", xfce_translators_pa },
  { "Persian", "fa_IR", xfce_translators_fa_IR },
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
  { "Urdu", "ur", xfce_translators_ur },
  { "Uyghur", "ug", xfce_translators_ug },
  { "Uzbek", "uz", xfce_translators_uz },
  { "Vietnamese", "vi", xfce_translators_vi },
  { "Welsh", "cy", xfce_translators_cy },
};
