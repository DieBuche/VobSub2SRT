/*
 *  This file is part of vobsub2srt
 *
 *  Copyright (C) 2010 Rüdiger Sonderfeld <ruediger@c-plusplus.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "langcodes.h++"
#include <functional>
#include <algorithm>
#include <cstring>
#include <cassert>

namespace {

static char const *const iso639_1[] = {
  "aa",
  "ab",
  "ae",
  "af",
  "ak",
  "am",
  "an",
  "ar",
  "as",
  "av",
  "ay",
  "az",
  "ba",
  "be",
  "bg",
  "bh",
  "bi",
  "bm",
  "bn",
  "bo",
  "br",
  "bs",
  "ca",
  "ce",
  "ch",
  "co",
  "cr",
  "cs",
  "cu",
  "cv",
  "cy",
  "da",
  "de",
  "dv",
  "dz",
  "ee",
  "el",
  "en",
  "eo",
  "es",
  "et",
  "eu",
  "fa",
  "ff",
  "fi",
  "fj",
  "fo",
  "fr",
  "fy",
  "ga",
  "gd",
  "gl",
  "gn",
  "gu",
  "gv",
  "ha",
  "he",
  "hi",
  "ho",
  "hr",
  "ht",
  "hu",
  "hy",
  "hz",
  "ia",
  "id",
  "ie",
  "ig",
  "ii",
  "ik",
  "io",
  "is",
  "it",
  "iu",
  "ja",
  "jv",
  "ka",
  "kg",
  "ki",
  "kj",
  "kk",
  "kl",
  "km",
  "kn",
  "ko",
  "kr",
  "ks",
  "ku",
  "kv",
  "kw",
  "ky",
  "la",
  "lb",
  "lg",
  "li",
  "ln",
  "lo",
  "lt",
  "lu",
  "lv",
  "mg",
  "mh",
  "mi",
  "mk",
  "ml",
  "mn",
  "mr",
  "ms",
  "mt",
  "my",
  "na",
  "nb",
  "nd",
  "ne",
  "ng",
  "nl",
  "nn",
  "no",
  "nr",
  "nv",
  "ny",
  "oc",
  "oj",
  "om",
  "or",
  "os",
  "pa",
  "pi",
  "pl",
  "ps",
  "pt",
  "qu",
  "rm",
  "rn",
  "ro",
  "ru",
  "rw",
  "sa",
  "sc",
  "sd",
  "se",
  "sg",
  "si",
  "sk",
  "sl",
  "sm",
  "sn",
  "so",
  "sq",
  "sr",
  "ss",
  "st",
  "su",
  "sv",
  "sw",
  "ta",
  "te",
  "tg",
  "th",
  "ti",
  "tk",
  "tl",
  "tn",
  "to",
  "tr",
  "ts",
  "tt",
  "tw",
  "ty",
  "ug",
  "uk",
  "ur",
  "uz",
  "ve",
  "vi",
  "vo",
  "wa",
  "wo",
  "xh",
  "yi",
  "yo",
  "za",
  "zh",
  "zu" };
static char const *const *const iso639_1_end = iso639_1 + sizeof(iso639_1)/sizeof(iso639_1[0]);

static char const *const iso639_3[] = {
  "aar",
  "abk",
  "ave",
  "afr",
  "aka",
  "amh",
  "arg",
  "ara",
  "asm",
  "ava",
  "aym",
  "aze",
  "bak",
  "bel",
  "bul",
  "bih",
  "bis",
  "bam",
  "ben",
  "tib",
  "bre",
  "bos",
  "cat",
  "che",
  "cha",
  "cos",
  "cre",
  "cze",
  "chu",
  "chv",
  "wel",
  "dan",
  "ger",
  "div",
  "dzo",
  "ewe",
  "gre",
  "eng",
  "epo",
  "spa",
  "est",
  "baq",
  "per",
  "ful",
  "fin",
  "fij",
  "fao",
  "fre",
  "fry",
  "gle",
  "gla",
  "glg",
  "grn",
  "guj",
  "glv",
  "hau",
  "heb",
  "hin",
  "hmo",
  "hrv",
  "hat",
  "hun",
  "arm",
  "her",
  "ina",
  "ind",
  "ile",
  "ibo",
  "iii",
  "ipk",
  "ido",
  "ice",
  "ita",
  "iku",
  "jpn",
  "jav",
  "geo",
  "kon",
  "kik",
  "kua",
  "kaz",
  "kal",
  "khm",
  "kan",
  "kor",
  "kau",
  "kas",
  "kur",
  "kom",
  "cor",
  "kir",
  "lat",
  "ltz",
  "lug",
  "lim",
  "lin",
  "lao",
  "lit",
  "lub",
  "lav",
  "mlg",
  "mah",
  "mao",
  "mac",
  "mal",
  "mon",
  "mar",
  "may",
  "mlt",
  "bur",
  "nau",
  "nob",
  "nde",
  "nep",
  "ndo",
  "dut",
  "nno",
  "nor",
  "nbl",
  "nav",
  "nya",
  "oci",
  "oji",
  "orm",
  "ori",
  "oss",
  "pan",
  "pli",
  "pol",
  "pus",
  "por",
  "que",
  "roh",
  "run",
  "rum",
  "rus",
  "kin",
  "san",
  "srd",
  "snd",
  "sme",
  "sag",
  "sin",
  "slo",
  "slv",
  "smo",
  "sna",
  "som",
  "alb",
  "srp",
  "ssw",
  "sot",
  "sun",
  "swe",
  "swa",
  "tam",
  "tel",
  "tgk",
  "tha",
  "tir",
  "tuk",
  "tgl",
  "tsn",
  "ton",
  "tur",
  "tso",
  "tat",
  "twi",
  "tah",
  "uig",
  "ukr",
  "urd",
  "uzb",
  "ven",
  "vie",
  "vol",
  "wln",
  "wol",
  "xho",
  "yid",
  "yor",
  "zha",
  "chi",
  "zul" };
static char const *const *const iso639_3_end = iso639_3 + sizeof(iso639_3)/sizeof(iso639_3[0]);

static bool compare(char const *lhs, char const *rhs) {
  return std::strcmp(lhs, rhs) < 0;
}

}

char const *iso639_1_to_639_3(char const *lang) {
  assert(sizeof(iso639_1) == sizeof(iso639_3)); 
  char const *const * i = std::lower_bound(iso639_1, iso639_1_end, lang, compare); // binary search
  if(i == iso639_1_end) {
    return 0x0;
  }
  else {
    return iso639_3[i - iso639_1];
  }
}
