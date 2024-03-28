namespace unicode
{
    using bit_operations::GetBits;
    using bit_operations::SetBits;

    //code unit of UTF-8
    using utf8 = unsigned char;

    //code unit of UTF-16
    using utf16 = unsigned short;

    //code unit of UTF-32
    using utf32 = unsigned int;

    //Unicode code point
    using CodePoint = unsigned int;

    const list<unsigned char> UTF8_BOM { 0b11101111, 0b10111011, 0b10111111 };

    const list<unsigned char> UTF16LE_BOM { 0b11111111, 0b11111110 };

    const list<unsigned char> UTF16BE_BOM { 0b11111110, 0b11111111 };

    const list<unsigned char> UTF32LE_BOM { 0b11111111, 0b11111110, 0b00000000, 0b00000000 };

    const list<unsigned char> UTF32BE_BOM { 0b00000000, 0b00000000, 0b11111110, 0b11111111 };

    const int UTF8_CODE_UNIT_LENGTH = 1; //in bytes

    const int UTF16_CODE_UNIT_LENGTH = 2; //in bytes

    const int UTF32_CODE_UNIT_LENGTH = 4; //in bytes

    ///BEGIN/END RANGES OF (BASIC MULTILINGUAL PLANE) SUBBLOCKS

    const int BASIC_MULTILINGUAL_PLANE_BEGIN = 0;
    const int BASIC_MULTILINGUAL_PLANE_END = 65535;

    const int SUPPLEMENTARY_MULTILINGUAL_PLANE_BEGIN = 65536;
    const int SUPPLEMENTARY_MULTILINGUAL_PLANE_END = 131071;

    const int SUPPLEMENTARY_IDEOGRAPHIC_PLANE_BEGIN = 131072;
    const int SUPPLEMENTARY_IDEOGRAPHIC_PLANE_END = 196607;

    const int SUPPLEMENTARY_SPECIAL_PURPOSE_PLANE_BEGIN = 917504;
    const int SUPPLEMENTARY_SPECIAL_PURPOSE_PLANE_END = 983039;

    const int PRIVATE_USE_AREA1_BEGIN = 57344;
    const int PRIVATE_USE_AREA1_END = 63743;

    const int PRIVATE_USE_AREA2_BEGIN = 983040;
    const int PRIVATE_USE_AREA2_END = 1048573;

    const int PRIVATE_USE_AREA3_BEGIN = 1048576;
    const int PRIVATE_USE_AREA3_END = 1114109;

    const int BASIC_LATIN_BEGIN = 0;
    const int BASIC_LATIN_END = 127;

    const int ARABIC_DIGITS_BEGIN = 48;
    const int ARABIC_DIGITS_END = 57;

    const int LATIN1_SUPPLEMENT_BEGIN = 128;
    const int LATIN1_SUPPLEMENT_END = 255;

    const int LATIN_EXTENDED_A_BEGIN = 256;
    const int LATIN_EXTENDED_A_END = 383;

    const int LATIN_EXTENDED_B_BEGIN = 384;
    const int LATIN_EXTENDED_B_END = 591;

    const int IPA_EXTENSIONS_BEGIN = 592;
    const int IPA_EXTENSIONS_END = 687;

    const int SPACING_MODIFIER_LETTERS_BEGIN = 688;
    const int SPACING_MODIFIER_LETTERS_END = 767;

    const int COMBINING_DIACRITICAL_MARKS_BEGIN = 768;
    const int COMBINING_DIACRITICAL_MARKS_END = 879;

    const int GREEK_AND_COPTIC_BEGIN = 880;
    const int GREEK_AND_COPTIC_END = 1023;

    const int CYRILLIC_BEGIN = 1024;
    const int CYRILLIC_END = 1279;

    const int CYRILLIC_SUPPLEMENT_BEGIN = 1280;
    const int CYRILLIC_SUPPLEMENT_END = 1327;

    const int ARMENIAN_BEGIN = 1328;
    const int ARMENIAN_END = 1423;

    const int HEBREW_BEGIN = 1424;
    const int HEBREW_END = 1535;

    const int ARABIC_BEGIN = 1536;
    const int ARABIC_END = 1791;

    const int SYRIAC_BEGIN = 1792;
    const int SYRIAC_END = 1871;

    const int ARABIC_SUPPLEMENT_BEGIN = 1872;
    const int ARABIC_SUPPLEMENT_END = 1919;

    const int THAANA_BEGIN = 1920;
    const int THAANA_END = 1983;

    const int NKO_BEGIN = 1984;
    const int NKO_END = 2047;

    const int SAMARITAN_BEGIN = 2048;
    const int SAMARITAN_END = 2111;

    const int MANDAIC_BEGIN = 2112;
    const int MANDAIC_END = 2143;

    const int SYRIAC_SUPPLEMENT_BEGIN = 2144;
    const int SYRIAC_SUPPLEMENT_END = 2159;

    const int ARABIC_EXTENED_B_BEGIN = 2160;
    const int ARABIC_EXTENDED_B_END = 2207;

    const int ARABIC_EXTENDED_A_BEGIN = 2208;
    const int ARABIC_EXTENDED_A_END = 2303;

    const int DEVANAGARI_BEGIN = 2304;
    const int DEVANAGARI_END = 2431;

    const int BENGALI_BEGIN = 2432;
    const int BENGALI_END = 2599;

    const int GURMUKHI_BEGIN = 2560;
    const int GURMUKHI_END = 2687;

    const int GUJARATI_BEGIN = 2688;
    const int GUJARATI_END = 2815;

    const int ORIYA_BEGIN = 2816;
    const int ORIYA_END = 2943;

    const int TAMIL_BEGIN = 2944;
    const int TAMIL_END = 3071;

    const int TELUGU_BEGIN = 3072;
    const int TELUGU_END = 3199;

    const int KANNADA_BEGIN = 3200;
    const int KANNADA_END = 3327;

    const int MALAYALAM_BEGIN = 3328;
    const int MALAYALAM_END = 3455;

    const int SINHALA_BEGIN = 3456;
    const int SINHALA_END = 3583;

    const int THAI_BEGIN = 3584;
    const int THAI_END = 3711;

    const int LAO_BEGIN = 3712;
    const int LAO_END = 3839;

    const int TIBETAN_BEGIN = 3840;
    const int TIBETAN_END = 4095;

    const int MYANMAR_BEGIN = 4096;
    const int MYANMAR_END = 4255;

    const int GEORGIAN_BEGIN = 4256;
    const int GEORGIAN_END = 4351;

    const int HANGUL_JAMO_BEGIN = 4352;
    const int HANGUL_JAMO_END = 4607;

    const int ETHIOPIC_BEGIN = 4608;
    const int ETHIOPIC_END = 4991;

    const int ETHIOPIC_SUPPLEMENT_BEGIN = 4992;
    const int ETHIOPIC_SUPPLEMENT_END = 5023;

    const int CHEROKEE_BEGIN = 5024;
    const int CHEROKEE_END = 5119;

    const int UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_BEGIN = 5120;
    const int UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_END = 5759;

    const int OGHAM_BEGIN = 5760;
    const int OGHAM_END = 5791;

    const int RUNIC_BEGIN = 5792;
    const int RUNIC_END = 5887;

    const int TAGALOG_BEGIN = 5888;
    const int TAGALOG_END = 5919;

    const int HANUOO_BEGIN = 5920;
    const int HANUOO_END = 5951;

    const int BUHID_BEGIN = 5952;
    const int BUHID_END = 5983;

    const int TAGBANWA_BEGIN = 5984;
    const int TAGBANWA_END = 6015;

    const int KHMER_BEGIN = 6016;
    const int KHMER_END = 6143;

    const int MONGOLIAN_BEGIN = 6144;
    const int MONGOLIAN_END = 6319;

    const int UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED_BEGIN = 6320;
    const int UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED_END = 6399;

    const int LIMBU_BEGIN = 6400;
    const int LIMBU_END = 6479;

    const int TAI_LE_BEGIN = 6480;
    const int TAI_LE_END = 6527;

    const int NEW_TAI_LUE_BEGIN = 6528;
    const int NEW_TAI_LUE_END = 6623;

    const int KHMER_SYMBOLS_BEGIN = 6624;
    const int KHMER_SYMBOLS_END = 6655;

    const int BUGINESE_BEGIN = 6656;
    const int BUGINESE_END = 6687;

    const int TAI_THAM_BEGIN = 6688;
    const int TAI_THAM_END = 6831;

    const int COMBINING_DIACRITICAL_MARKS_EXTENDED_BEGIN = 6832;
    const int COMBINING_DIACRITICAL_MARKS_EXTENDED_END = 6911;

    const int BALINESE_BEGIN = 6912;
    const int BALINESE_END = 7039;

    const int SUNDANESE_BEGIN = 7040;
    const int SUNDANESE_END = 7103;

    const int BATAK_BEGIN = 7104;
    const int BATAK_END = 7167;

    const int LEPCHA_BEGIN = 7168;
    const int LEPCHA_END = 7247;

    const int OL_CHIKI_BEGIN = 7248;
    const int OL_CHIKI_END = 7295;

    const int CYRILLIC_EXTENDED_C_BEGIN = 7296;
    const int CYRILLIC_EXTENDED_C_END = 7311;

    const int GEORGIAN_EXTENDED_BEGIN = 7312;
    const int GEORGIAN_EXTENDED_END = 7359;

    const int SUNDANESE_SUPPLEMENT_BEGIN = 7360;
    const int SUNDANESE_SUPPLEMENT_END = 7375;

    const int VEDIC_EXTENSIONS_BEGIN = 7376;
    const int VEDIC_EXTENSIONS_END = 7423;

    const int PHONETIC_EXTENSIONS_BEGIN = 7424;
    const int PHONETIC_EXTENSIONS_END = 7551;

    const int PHONETIC_EXTENSIONS_SUPPLEMENT_BEGIN = 7552;
    const int PHONETIC_EXTENSIONS_SUPPLEMENT_END = 7615;

    const int COMBINING_DIACRITICAL_MARKS_SUPPLEMENT_BEGIN = 7616;
    const int COMBINING_DIACRITICAL_MARKS_SUPPLEMENT_END = 7679;

    const int LATIN_EXTENDED_ADDITIONAL_BEGIN = 7680;
    const int LATIN_EXTENDED_ADDITIONAL_END = 7935;

    const int GREEK_EXTENDED_BEGIN = 7936;
    const int GREEK_EXTENDED_END = 8191;

    const int GENERAL_PUNCTUATION_BEGIN = 8192;
    const int GENERAL_PUNCTUATION_END = 8303;

    const int SUPERSCRIPTS_AND_SUBSCRIPTS_BEGIN = 8304;
    const int SUPERSCRIPTS_AND_SUBSCRIPTS_END = 8351;

    const int CURRENCY_SYMBOLS_BEGIN = 8352;
    const int CURRENCY_SYMBOLS_END = 8399;

    const int COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS_BEGIN = 8400;
    const int COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS_END = 8447;

    const int LETTERLIKE_SYMBOLS_BEGIN = 8448;
    const int LETTERLIKE_SYMBOLS_END = 8527;

    const int NUMBER_FORMS_BEGIN = 8528;
    const int NUMBER_FORMS_END = 8591;

    const int ARROWS_BEGIN = 8592;
    const int ARROWS_END = 8703;

    const int MATHEMATICAL_OPERATORS_BEGIN = 8704;
    const int MATHEMATICAL_OPERATORS_END = 8959;

    const int MISCELLANEOUS_TECHNICAL_BEGIN = 8960;
    const int MISCELLANEOUS_TECHNICAL_END = 9215;

    const int CONTROL_PICTURES_BEGIN = 9216;
    const int CONTROL_PICTURES_END = 9279;

    const int OPTICAL_CHARACTER_RECOGNITION_BEGIN = 9280;
    const int OPTICAL_CHARACTER_RECOGNITION_END = 9311;

    const int ENCLOSED_ALPHANUMERICS_BEIGN = 9312;
    const int ENCLOSED_ALPHANUMERICS_END = 9471;

    const int BOX_DRAWING_BEGIN = 9472;
    const int BOX_DRAWING_END = 9599;

    const int BLOCK_ELEMENTS_BEGIN = 9600;
    const int BLOCK_ELEMENTS_END = 9631;

    const int GEOMETRIC_SHAPES_BEGIN = 9632;
    const int GEOMETRIC_SHAPES_END = 9727;

    const int MISCELLANEOUS_SYMBOLS_BEGIN = 9728;
    const int MISCELLANEOUS_SYMBOLS_END = 9983;

    const int DINGBATS_BEGIN = 9984;
    const int DINGBATS_END = 10175;

    const int MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A_BEGIN = 10176;
    const int MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A_END = 10223;

    const int SUPPLEMENTAL_ARROWS_A_BEGIN = 10224;
    const int SUPPLEMENTAL_ARROWS_A_END = 10239;

    const int BRAILLE_PATTERNS_BEGIN = 10240;
    const int BRAILLE_PATTERNS_END = 10495;

    const int SUPPLEMENTAL_ARROWS_B_BEGIN = 10496;
    const int SUPPLEMENTAL_ARROWS_B_END = 10623;

    const int MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B_BEGIN = 10624;
    const int MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B_END = 10751;

    const int SUPPLEMENTAL_MATHEMATICAL_OPERATORS_BEGIN = 10752;
    const int SUPPLEMENTAL_MATHEMATICAL_OPERATORS_END = 11007;

    const int MISCELLANEOUS_SYMBOLS_AND_ARROWS_BEIGN = 11008;
    const int MISCELLANEOUS_SYMBOLS_AND_ARROWS_END = 11263;

    const int GLATOLITIC_BEGIN = 11264;
    const int GLATOLITIC_END = 11359;

    const int LATIN_EXTENDED_C_BEGIN = 11360;
    const int LATIN_EXTENDED_C_END = 11391;

    const int COPTIC_BEIGN = 11392;
    const int COPTIC_END = 11519;

    const int GEORGIAN_SUPPLEMENT_BEGIN = 11520;
    const int GEORGIAN_SUPPLEMENT_END = 11567;

    const int TIFINAGH_BEGIN = 11568;
    const int TIFINAGH_END = 11647;

    const int ETHIOPIC_EXTENDED_BEGIN = 11648;
    const int ETHIOPIC_EXTENDED_END = 11743;

    const int CYRILLIC_EXTENDED_A_BEGIN = 11744;
    const int CYRILLIC_EXTENDED_A_END = 11775;

    const int SUPPLEMENTAL_PUNCTUATION_BEGIN = 11776;
    const int SUPPLEMENTAL_PUNCTUATION_END = 11903;

    const int CJK_RADICALS_SUPPLEMENT_BEGIN = 11904;
    const int CJK_RADICALS_SUPPLEMENT_END = 12031;

    const int KANGXI_RADICALS_BEGIN = 12032;
    const int KANGXI_RADICALS_END = 12255;

    const int IDEOGRAPHIC_DESCRIPTION_CHARACTERS_BEGIN = 12272;
    const int IDEOGRAPHIC_DESCRIPTIONS_CHARACTERS_END = 12287;

    const int CJK_SYMBOLS_AND_PUNCTUATION_BEGIN = 12288;
    const int CJK_SYMBOLS_AND_PUNCTUATION_END = 12351;

    const int HIRAGANA_BEGIN = 12352;
    const int HIRAGANA_END = 12447;

    const int KATAKANA_BEGIN = 12448;
    const int KATAKANA_END = 12543;

    const int BOPOMOFO_BEGIN = 12544;
    const int BOPOMOFO_END = 12591;

    const int HANGUL_COMPATIBILITY_JAMO_BEGIN = 12592;
    const int HANGUL_COMPATIBILITY_JAMO_END = 12687;

    const int KANBUN_BEGIN = 12688;
    const int KANBUN_END = 12703;

    const int BOPOMOFO_EXTENDED_BEGIN = 12704;
    const int BOPOMOFO_EXTENDED_END = 12735;

    const int CJK_STROKES_BEGIN = 12736;
    const int CJK_STROKES_END = 12783;

    const int KATAKANA_PHONETIC_EXTENSIONS_BEGIN = 12784;
    const int KATAKANA_PHONETIC_EXTENSIONS_END = 12799;

    const int ENCLOSED_CJK_LETTERS_AND_MONTHS_BEGIN = 12800;
    const int ENCLOSED_CJK_LETTERS_AND_MONTHS_END = 13055;

    const int CJK_COMPATIBILITY_BEGIN = 13056;
    const int CJK_COMPATIBILITY_END = 13311;

    const int CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A_BEGIN = 13312;
    const int CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A_END = 19903;

    const int YIJING_HEXAGRAM_SYMBOLS_BEGIN = 19904;
    const int YIJING_HEXAGRAM_SYMBOLS_END = 19967;

    const int CJK_UNIFIED_IDEOGRAPHS_BEGIN = 19968;
    const int CJK_UNIIFED_IDEOGRAPHS_END = 40959;

    const int YI_SYLLABLES_BEGIN = 40960;
    const int YI_SYLLABLES_END = 42127;

    const int YI_RADICALS_BEGIN = 42128;
    const int YI_RADICALS_END = 42191;

    const int LISU_BEGIN = 42192;
    const int LISU_END = 42239;

    const int VAI_BEGIN = 42240;
    const int VAI_END = 42559;

    const int CYRILLIC_EXTENDED_B_BEGIN = 42560;
    const int CYRILLIC_EXTENDED_B_END = 42655;

    const int BAMUM_BEGIN = 42656;
    const int BAMUM_END = 42751;

    const int MODIFIER_TONE_LETTERS_BEGIN = 42752;
    const int MODIFIER_TONE_LETTERS_END = 42783;

    const int LATIN_EXTENDED_D_BEGIN = 42784;
    const int LATIN_EXTENDED_D_END = 43007;

    const int SYLOTI_NAGRI_BEGIN = 43008;
    const int SYLOTI_NAGRI_END = 43055;

    const int COMMON_INDIC_NUMBER_FORMS_BEGIN = 43056;
    const int COMMON_INDIC_NUMBER_FOMRS_END = 43071;

    const int PHAGS_PA_BEGIN = 43072;
    const int PHAGS_PA_END = 43135;

    const int SAURASHTRA_BEGIN = 43136;
    const int SAURASHTRA_END = 43231;

    const int DEVANAGARI_EXTENDED_BEGIN = 43232;
    const int DEVANAGARI_EXTENDED_END = 43263;

    const int KAYAH_LI_BEGIN = 43264;
    const int KAYAH_LI_END = 43311;

    const int REJANG_BEGIN = 43312;
    const int REJANG_END = 43359;

    const int HANGUL_JAMO_EXTENDED_A_BEGIN = 43360;
    const int HANGUL_JAMO_EXTENDED_A_END = 43391;

    const int JAVANESE_BEGIN = 43392;
    const int JAVANESE_END = 43487;

    const int MYANMAR_EXTENDED_B_BEGIN = 43488;
    const int MYANMAR_EXTENDED_B_END = 43519;

    const int CHAM_BEGIN = 43520;
    const int CHAM_END = 43615;

    const int MYANMAR_EXTENDED_A_BEGIN = 43616;
    const int MYANMAR_EXTENDED_A_END = 43647;

    const int TAI_VIET_BEGIN = 43648;
    const int TAI_VIET_END = 43743;

    const int MEETEI_MAYEK_EXTENSIONS_BEGIN = 43744;
    const int MEETEI_MAYEK_EXTENSIONS_END = 43775;

    const int ETHIOPIC_EXTENDED_A_BEGIN = 43776;
    const int ETHIOPIC_EXTENDED_A_END = 43823;

    const int LATIN_EXTENDED_E_BEGIN = 43824;
    const int LATIN_EXTENDED_E_END = 43887;

    const int CHEROKEE_SUPPLEMENT_BEGIN = 43888;
    const int CHEROKEE_SUPPLEMENT_END = 43967;

    const int MEETEI_MAYEK_BEGIN = 43968;
    const int MEETEI_MAYEK_END = 44031;

    const int HANGUL_SYLLABLES_BEGIN = 44032;
    const int HANGUL_SYLLABLES_END = 55215;

    const int HANGUL_JAMO_EXTENDED_B_BEGIN = 55216;
    const int HANGUL_JAMO_EXTENDED_B_END = 55295;

    const int HIGH_SURROGATES_BEGIN = 55296;
    const int HIGH_SURROGATES_END = 56319;

    const int HIGH_SURROGATES_NON_PRIVATE_BEGIN = 55296;
    const int HIGH_SURROGATES_NON_PRIVATE_END = 56191;

    const int HIGH_PRIVATE_USE_SURROGATES_BEGIN = 56192;
    const int HIGH_PRIVATE_USE_SURROGATES_END = 56319;

    const int LOW_SURROGATES_BEGIN = 56320;
    const int LOW_SURROGATES_END = 57343;

    const int PRIVATE_USE_AREA_BEGIN = 57344;
    const int PRIVATE_USE_AREA_END = 63743;

    const int CJK_COMPATIBILITY_IDEOGRAPHS_BEGIN = 63744;
    const int CJK_COMPATIBILITY_IDEOGRAPHS_END = 64255;

    const int ALPHABETIC_PRESENTATION_FORMS_BEGIN = 64256;
    const int ALPHABETIC_PRESENTATION_FORMS_END = 64335;

    const int ARABIC_PRESENTATION_FORMS_A_BEGIN = 64336;
    const int ARABIC_PRESENTATION_FORMS_A_END = 65023;

    const int VARIATION_SELECTORS_BEGIN = 65024;
    const int VARIATION_SELECTORS_END = 65039;

    const int VERTICAL_FORMS_BEGIN = 65040;
    const int VERTICAL_FORMS_END = 65055;

    const int COMBINING_HALF_MARKS_BEGIN = 65056;
    const int COMBINING_HALF_MARKS_END = 65071;

    const int CJK_COMPATIBILITY_FORMS_BEGIN = 65072;
    const int CJK_COMPATIBILITY_FORMS_END = 65103;

    const int SMALL_FORM_VARIANTS_BEGIN = 65104;
    const int SMALL_FORM_VARIANTS_END = 65135;

    const int ARABIC_PRESENTATION_FORMS_B_BEGIN = 65136;
    const int ARABIC_PRESENTATION_FORMS_B_END = 65279;

    const int HALFWIDTH_AND_FULLWIDTH_FORMS_BEGIN = 65280;
    const int HALFWIDTH_AND_FULLWIDTH_FORMS_END = 65519;

    const int SPECIALS_BEGIN = 65520;
    const int SPECIALS_END = 65535;

    ///BEGIN/END RANGES OF (SUPPLEMENTARY MULTILINGUAL PLANE) SUBBLOCKS

    const int LINEAR_B_SYLLABARY_BEGIN = 65536;
    const int LINEAR_B_SYLLABARY_END = 65663;

    const int LINEAR_B_IDEOGRAMS_BEGIN = 65664;
    const int LINEAR_B_IDEOGRAMS_END = 65791;

    const int AEGEAN_NUMBERS_BEGIN = 65792;
    const int AEGEAN_NUMBERS_END = 65855;

    const int ANCIENT_GREEK_NUMBERS_BEGIN = 65856;
    const int ANCIENT_GREEK_NUMBERS_END = 65935;

    const int ANCIENT_SYMBOLS_BEGIN = 65936;
    const int ANCIENT_SYMBOLS_END = 65999;

    const int PHAISTOS_DISC_BEGIN = 66000;
    const int PHAISTOS_DISC_END = 66047;

    const int LYCIAN_BEGIN = 66176;
    const int LYCIAN_END = 66207;

    const int CARIAN_BEGIN = 66208;
    const int CARIAN_END = 66271;

    const int COPTIC_EPACT_NUMEBRS_BEGIN = 66272;
    const int COPTIC_EPACT_NUMBERS_END = 66303;

    const int OLD_ITALIC_BEGIN = 66304;
    const int OLD_ITALIC_END = 66351;

    const int GOTHIC_BEGIN = 66352;
    const int GOTHIC_END = 66383;

    const int OLD_PERMIC_BEGIN = 66384;
    const int OLD_PERMIC_END = 66431;

    const int UGARITIC_BEGIN = 66432;
    const int UGARITIC_END = 66463;

    const int OLD_PERSIAN_BEGIN = 66464;
    const int OLD_PERSIAN_END = 66527;

    const int DESERET_BEGIN = 66560;
    const int DESERET_END = 66639;

    const int SHAVIAN_BEGIN = 66640;
    const int SHAVIAN_END = 66687;

    const int OSMANYA_BEGIN = 66688;
    const int OSMANYA_END = 66735;

    const int OSAGE_BEGIN = 66736;
    const int OSAGE_END = 66815;

    const int ELBASAN_BEGIN = 66816;
    const int ELBASAN_END = 66863;

    const int CAUCASIAN_ALBANIAN_BEGIN = 66864;
    const int CAUCASIAN_ALBANIAN_END = 66927;

    const int VITHKUQI_BEGIN = 66928;
    const int VITHKUQI_END = 67007;

    const int LINEAR_A_BEGIN = 67072;
    const int LINEAR_A_END = 67455;

    const int LATIN_EXTENDED_F_BEGIN = 67456;
    const int LATIN_EXTENDED_F_END = 67519;

    const int CYPRIOT_SYLLABARY_BEGIN = 67584;
    const int CYPRIOT_SYLLABARY_END = 67647;

    const int IMPERIAL_ARAMAIC_BEGIN = 67648;
    const int IMPERIAL_ARAMAIC_END = 67679;

    const int PALMYRENE_BEGIN = 67680;
    const int PALMYRENE_END = 67711;

    const int NABATAEAN_BEGIN = 67712;
    const int NABATAEAN_END = 67759;

    const int HATRAN_BEGIN = 67808;
    const int HATRAN_END = 67839;

    const int PHOENICIAN_BEGIN = 67840;
    const int PHOENICIAN_END = 67871;

    const int LYDIAN_BEIGN = 67872;
    const int LYDIAN_END = 67903;

    const int MEROITIC_HIEROGLYPHS_BEGIN = 67968;
    const int MEROITIC_HIEROGLYPHS_END = 67999;

    const int MEROITIC_CURSIVE_BEGIN = 68000;
    const int MEROITIC_CURSIVE_END = 68095;

    const int KHAROSHTHI_BEGIN = 68096;
    const int KHAROSHTHI_END = 68191;

    const int OLD_SOUTH_ARABIAN_BEGIN = 68192;
    const int OLD_SOUTH_ARABIAN_END = 68223;

    const int OLD_NORTH_ARABIAN_BEGIN = 68224;
    const int OLD_NORTH_ARABIAN_END = 68255;

    const int MANICHAEAN_BEGIN = 68288;
    const int MANICHAEAN_END = 68351;

    const int AVESTAN_BEGIN = 68352;
    const int AVESTAN_END = 68415;

    const int INSCRIPTIONAL_PARTHIAN_BEGIN = 68416;
    const int INSCRIPTIONAL_PARTHIAN_END = 68447;

    const int INSCRIPTIONAL_PAHLAVI_BEGIN = 68448;
    const int INSCRIPTIONAL_PAHLAVI_END = 68479;

    const int PSALTER_PAHLAVI_BEGIN = 68480;
    const int PSALTER_PAHLAVI_END = 68527;

    const int OLD_TURKIC_BEGIN = 68608;
    const int OLD_TURKIC_END = 68687;

    const int OLD_HUNGARIAN_BEGIN = 68736;
    const int OLD_HUNGARIAN_END = 68863;

    const int HANIFI_ROHINGYA_BEGIN = 68864;
    const int HANIFI_ROHINGYA_END = 68927;

    const int RUMI_NUMERAL_SYMBOLS_BEGIN = 69216;
    const int RUMI_NUMERAL_SYMBOLS_END = 69247;

    const int YEZIDI_BEGIN = 69248;
    const int YEZIDI_END = 69311;

    const int ARABIC_EXTENDED_C_BEGIN = 69312;
    const int ARABIC_EXTENDED_C_END = 69375;

    const int OLD_SOGDIAN_BEGIN = 69376;
    const int OLD_SOGDIAN_END = 69423;

    const int SOGDIAN_BEGIN = 69424;
    const int SOGDIAN_END = 69487;

    const int OLD_UYGHUR_BEGIN = 69488;
    const int OLD_UYGHUR_END = 69551;

    const int CHORASMIAN_BEGIN = 69552;
    const int CHORASMIAN_END = 69599;

    const int ELYMAIC_BEGIN = 69600;
    const int ELYMAIC_END = 69631;

    const int BRAHMI_BEGIN = 69632;
    const int BRAHMI_END = 69759;

    const int KAITHI_BEGIN = 69760;
    const int KAITHI_END = 69839;

    const int SORA_SOMPENG_BEGIN = 69840;
    const int SORA_SOMPENG_END = 69887;

    const int CHAKMA_BEGIN = 69888;
    const int CHAKMA_END = 69967;

    const int MAHAJANI_BEGIN = 69968;
    const int MAHAJANI_END = 70015;

    const int SHARADA_BEGIN = 70016;
    const int SHARADA_END = 70111;

    const int SINHALA_ARCHAIC_NUMBERS_BEGIN = 70112;
    const int SINHALA_ARCHAIC_NUMBERS_END = 70143;

    const int KHOJKI_BEGIN = 70144;
    const int KHOJKI_END = 70223;

    const int MULTANI_BEGIN = 70272;
    const int MULTANI_END = 70319;

    const int KHUDAWADI_BEGIN = 70320;
    const int KHUDAWADI_END = 70399;

    const int GRANTHA_BEGIN = 70400;
    const int GRANTHA_END = 70527;

    const int NEWA_BEGIN = 70656;
    const int NEWA_END = 70783;

    const int TIRHUTA_BEGIN = 70784;
    const int TIRHUTA_END = 70879;

    const int SIDDHAM_BEGIN = 71040;
    const int SIDDHAM_END = 71167;

    const int MODI_BEGIN = 71168;
    const int MODI_END = 71263;

    const int MONGOLIAN_SUPPLEMENT_BEGIN = 71264;
    const int MONGOLIAN_SUPPLEMENT_END = 71295;

    const int TAKRI_BEGIN = 71296;
    const int TAKRI_END = 71375;

    const int AHOM_BEGIN = 71424;
    const int AHOM_END = 71503;

    const int DOGRA_BEGIN = 71680;
    const int DOGRA_END = 71759;

    const int WARANG_CITI_BEGIN = 71840;
    const int WARANG_CITI_END = 71935;

    const int DIVES_AKURU_BEGIN = 71936;
    const int DIVES_AKURU_END = 72031;

    const int NANDINAGARI_BEGIN = 72096;
    const int NANDINAGARI_END = 72191;

    const int ZANABAZAR_SQUARE_BEGIN = 72192;
    const int ZANABAZAR_SQUARE_END = 72271;

    const int SOYOMBO_BEGIN = 72272;
    const int SOYOMBO_END = 72367;

    const int PAU_CIN_HAU_BEGIN = 72384;
    const int PAU_CIN_HAU_END = 72447;

    const int DEVANAGARI_EXTENDED_A_BEGIN = 72448;
    const int DEVANAGARI_EXTENDED_A_END = 72543;

    const int BHAIKSUKI_BEGIN = 72704;
    const int BHAIKSUKI_END = 72815;

    const int MARCHEN_BEGIN = 72816;
    const int MARCHEN_END = 72895;

    const int MASARAM_GONDI_BEGIN = 72960;
    const int MASARAM_GONDI_END = 73055;

    const int GUNJALA_GONDI_BEGIN = 73056;
    const int GUNJALA_GONDI_END = 73135;

    const int MAKASAR_BEGIN = 73440;
    const int MAKASAR_END = 73471;

    const int KAWI_BEGIN = 73472;
    const int KAWI_END = 73567;

    const int LISU_SUPPLEMENT_BEGIN = 73648;
    const int LISU_SUPPLEMENT_END = 73663;

    const int TAMIL_SUPPLEMENT_BEGIN = 73664;
    const int TAMIL_SUPPLEMENT_END = 73727;

    const int CUNEIFORM_BEIGN = 73728;
    const int CUNEIFORM_END = 74751;

    const int CUNEIFORM_NUMBERS_AND_PUNCTUATION_BEGIN = 74752;
    const int CUNEIFORM_NUMBERS_AND_PUNCTUATION_END = 74879;

    const int EARLY_DYNASTIC_CUNEIFORM_BEGIN = 74880;
    const int EARLY_DYNASTIC_CUNEIFORM_END = 75087;

    const int CYPRO_MINOAN_BEGIN = 77712;
    const int CYPRO_MINOAN_END = 77823;

    const int EGYPTIAN_HIEROGLYPHS_BEGIN = 77824;
    const int EGYPTIAN_HIEROGLYPHS_END = 78895;

    const int EGYPTIAN_HIEROGLYPH_FORMAT_CONTROLS_BEGIN = 78896;
    const int EGYPTIAN_HIEROGLYPH_FORMAT_CONTROLS_END = 78943;

    const int ANATOLIAN_HIEROGLYPHS_BEGIN = 82944;
    const int ANATOLIAN_HIEROGLYPHS_END = 83583;

    const int BAMUM_SUPPLEMENT_BEGIN = 92160;
    const int BAMUM_SUPPLEMENT_END = 92735;

    const int MRO_BEGIN = 92736;
    const int MRO_END = 92783;

    const int TANGSA_BEGIN = 92784;
    const int TANGSA_END = 92789;

    const int BASSA_VAH_BEGIN = 92880;
    const int BASSA_VAN_END = 92927;

    const int PAHAWH_HMONG_BEGIN = 92928;
    const int PAHAWH_HMONG_END = 93071;

    const int MEDEFAIDRIN_BEGIN = 93760;
    const int MEDEFAIDRIN_END = 93855;

    const int MIAO_BEGIN = 93952;
    const int MIAO_END = 94111;

    const int IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION_BEGIN = 94176;
    const int IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION_END = 94207;

    const int TANGUT_BEGIN = 94208;
    const int TANGUT_END = 100351;

    const int TANGUT_COMPONENTS_BEGIN = 100352;
    const int TANGUT_COMPONENTS_END = 101119;

    const int KHITAN_SMALL_SCRIPT_BEGIN = 101120;
    const int KHITAN_SMALL_SCRIPT_END = 101631;

    const int TANGUT_SUPPLEMENT_BEGIN = 101632;
    const int TANGUT_SUPPLEMENT_END = 101759;

    const int KANA_EXTENDED_B_BEGIN = 110576;
    const int KANA_EXTENDED_B_END = 110591;

    const int KANA_SUPPLEMENT_BEGIN = 110592;
    const int KANA_SUPPLEMENT_END = 110847;

    const int KANA_EXTENDED_A_BEGIN = 110848;
    const int KANA_EXTENDED_A_END = 110895;

    const int SMALL_KANA_EXTENSION_BEGIN = 110896;
    const int SMALL_KANA_EXTENSION_END = 110959;

    const int NUSHU_BEGIN = 110960;
    const int NUSHU_END = 111359;

    const int DUPLOYAN_BEGIN = 113664;
    const int DUPLOYAN_END = 113823;

    const int SHORTHAND_FORMAT_CONTROLS_BEGIN = 113824;
    const int SHORTHAND_FORMAT_CONTROLS_END = 113839;

    const int ZNAMENNY_MUSICAL_NOTATION_BEGIN = 118528;
    const int ZNAMENNY_MUSICAL_NOTATION_END = 118735;

    const int BYZANTINE_MUSICAL_SYMBOLS_BEGIN = 118784;
    const int BYZANTINE_MUSICAL_SYMBOLS_END = 119039;

    const int MUSICAL_SYMBOLS_BEGIN = 119040;
    const int MUSICAL_SYMBOLS_END = 119295;

    const int ANCIENT_GREEK_MUSICAL_NOTATION_BEGIN = 119296;
    const int ANCIENT_GREEK_MUSICAL_NOTATION_END = 119375;

    const int KAKTOVIK_NUMERALS_BEGIN = 119488;
    const int KAKTOVIK_NUMERALAS_END = 119519;

    const int MAYAN_NUMERALS_BEGIN = 119520;
    const int MAYAN_NUMERALS_END = 119551;

    const int TAI_XUAN_JING_SYMBOLS_BEGIN = 119552;
    const int TAI_XUAN_JING_SYMBOLS_END = 119647;

    const int COUNTING_ROD_NUMERALS_BEGIN = 119648;
    const int COUNTING_ROD_NUMERALS_END = 119679;

    const int MATHEMATICAL_ALPHANUMERIC_SYMBOLS_BEGIN = 119808;
    const int MATHEMATICAL_ALPHANUMERIC_SYMBOLS_END = 120831;

    const int SUTTON_SIGNWRITING_BEGIN = 120832;
    const int SUTTON_SIGNWRITING_END = 121519;

    const int LATIN_EXTENDED_G_BEGIN = 122624;
    const int LATIN_EXTENDED_G_END = 122879;

    const int GLAGOLITIC_SUPPLEMENT_BEGIN = 122880;
    const int GLAGOLITIC_SUPPLEMENT_END = 122927;

    const int CYRILLIC_EXTENDED_D_BEGIN = 122928;
    const int CYRILLIC_EXTENDED_D_END = 123023;

    const int NYIAKENG_PUACHUE_HMONG_BEGIN = 123136;
    const int NYIAKENG_PUACHUE_HMONG_END = 123215;

    const int TOTO_BEGIN = 123536;
    const int TOTO_END = 123583;

    const int WANCHO_BEGIN = 123584;
    const int WANCHO_END = 123647;

    const int NAG_MUNDARI_BEGIN = 124112;
    const int NAG_MUNDARI_END = 124159;

    const int ETHIOPIC_EXTENDED_B_BEGIN = 124896;
    const int ETHIOPIC_EXTENDED_B_END = 124927;

    const int MENDE_KIKAKUI_BEGIN = 124928;
    const int MENDE_KIKAKUI_END = 125151;

    const int ADLAM_BEGIN = 125184;
    const int ADLAM_END = 125279;

    const int INDIC_SIYAQ_NUMBERS_BEGIN = 126064;
    const int INDIC_SIYAQ_NUMBERS_END = 126143;

    const int OTTOMAN_SIYAQ_NUMBERS_BEGIN = 126208;
    const int OTTOMAN_SIYAQ_NUMBERS_END = 126287;

    const int ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS_BEGIN = 126464;
    const int ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS_END = 126719;

    const int MAHJONG_TILES_BEGIN = 126976;
    const int MAHJONG_TILES_END = 127023;

    const int DOMINO_TILES_BEIGN = 127024;
    const int DOMINO_TILES_END = 127135;

    const int PLAYING_CARDS_BEGIN = 127136;
    const int PLAYING_CARDS_END = 127231;

    const int ENCLOSED_ALPHANUMERIC_SUPPLEMENT_BEGIN = 127232;
    const int ENCLOSED_ALPHANUMERIC_SUPPLEMENT_END = 127487;

    const int ENCLOSED_IDEOGRAPHIC_SUPPLEMENT_BEGIN = 127488;
    const int ENCLOSED_IDEOGRAPHIC_SUPPLEMENT_END = 127743;

    const int MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS_BEGIN = 127744;
    const int MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS_END = 128511;

    const int EMOTICONS_BEGIN = 128512;
    const int EMOTICONS_END = 128591;

    const int ORNAMENTAL_DINGBATS_BEGIN = 128592;
    const int ORNAMENTAL_DINGBATS_END = 128639;

    const int TRANSPORT_AND_MAP_SYMBOLS_BEGIN = 128640;
    const int TRANSPORT_AND_MAP_SYMBOLS_END = 128767;

    const int ALCHEMICAL_SYMBOLS_BEGIN = 128768;
    const int ALCHEMICAL_SYMBOLS_END = 128895;

    const int GEOMETRIC_SHAPES_EXTENDED_BEGIN = 128896;
    const int GEOMETRIC_SHAPES_EXTENDED_END = 129023;

    const int SUPPLEMENTAL_ARROWS_C_BEGIN = 129024;
    const int SUPPLEMENTAL_ARROWS_C_END = 129279;

    const int SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS_BEGIN = 129280;
    const int SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS_END = 129535;

    const int CHESS_SYMBOLS_BEGIN = 129536;
    const int CHESS_SYMBOLS_END = 129647;

    const int SYMBOLS_AND_PICTOGRAPHS_EXTENDED_A_BEGIN = 129648;
    const int SYMBOLS_AND_PICTOGRAPHS_EXTENDED_A_END = 129791;

    const int SYMBOLS_FOR_LEGACY_COMPUTING_BEGIN = 129792;
    const int SYMBOLS_FOR_LEGACY_COMPUTING_END = 130047;

    ///FUNCTIONS

    //determines if the code point is whitepsace character (characters with property WS/WSpace/White_Space = Yes)
    bool IsWhitespace(CodePoint _character)
    {
        return _character == 9 || _character == 10 || _character == 11 || _character == 12 || _character == 13 || _character == 32 ||
               _character == 133 || _character == 160 || _character == 5760 || (_character >= 8192 && _character <= 8202) ||
               _character == 8232 || _character == 8233 || _character == 8239 || _character == 8287 || _character == 12288;
    }

    //determines if the code point is an arabic digit
    bool IsDigit(CodePoint _character)
    {
        return _character >= ARABIC_DIGITS_BEGIN && _character <= ARABIC_DIGITS_END;
    }

    bool IsHighSurrogate(utf16 _codeUnit)
    {
        return _codeUnit >= HIGH_SURROGATES_BEGIN && _codeUnit <= HIGH_SURROGATES_END;
    }

    bool IsLowSurrogate(utf16 _codeUnit)
    {
        return _codeUnit >= LOW_SURROGATES_BEGIN && _codeUnit <= LOW_SURROGATES_END;
    }

    //determines if the code point is part of Basic Multilingual Plane (it doesn't include the surrogate range)
    bool IsBMP(CodePoint _codePoint)
    {
        return _codePoint < HIGH_SURROGATES_BEGIN || (_codePoint > LOW_SURROGATES_END && _codePoint <= BASIC_MULTILINGUAL_PLANE_END);
    }

    //determines if the code point is part of Supplementary Multilingual Plane
    bool IsSMP(CodePoint _codePoint)
    {
        return _codePoint >= SUPPLEMENTARY_MULTILINGUAL_PLANE_BEGIN && _codePoint <= SUPPLEMENTARY_MULTILINGUAL_PLANE_END;
    }

    //determines if the code point is part of Supplementary Ideographic Plane
    bool IsSIP(CodePoint _codePoint)
    {
        return _codePoint >= SUPPLEMENTARY_IDEOGRAPHIC_PLANE_BEGIN && _codePoint <= SUPPLEMENTARY_IDEOGRAPHIC_PLANE_END;
    }

    //determines if the code point is part of Supplementary Special-purpose Plane
    bool IsSSP(CodePoint _codePoint)
    {
        return _codePoint >= SUPPLEMENTARY_SPECIAL_PURPOSE_PLANE_BEGIN && _codePoint <= SUPPLEMENTARY_SPECIAL_PURPOSE_PLANE_END;
    }

    //determines if the code point is part of Private Use Area
    bool IsPUA(CodePoint _codePoint)
    {
        return _codePoint >= PRIVATE_USE_AREA1_BEGIN && _codePoint <= PRIVATE_USE_AREA1_END;
    }

    //determines if the code point is part of (Supplementary Private Use Area-A)
    bool IsPUA2(CodePoint _codePoint)
    {
        return _codePoint >= PRIVATE_USE_AREA2_BEGIN && _codePoint <= PRIVATE_USE_AREA2_END;
    }

    //determines if the code point is part of (Supplementary Private Use Area-B)
    bool IsPUA3(CodePoint _codePoint)
    {
        return _codePoint >= PRIVATE_USE_AREA3_BEGIN && _codePoint <= PRIVATE_USE_AREA3_END;
    }

    //returns (high surrogate, low surrogate)
    //_codePoint is not a code point from BMP ->
    t2<utf16, utf16> GetSurrogatePair(CodePoint _codePoint)
    {
        unsigned int number = (_codePoint - 65536);
        utf16 highSurrogate = (number >> 10) + HIGH_SURROGATES_BEGIN;
        utf16 lowSurrogate = ((number << 22) >> 22) + LOW_SURROGATES_END;
        return t2<utf16, utf16>(highSurrogate, lowSurrogate);
    }

    //the parameters rerpesents UTF-8 character that is part of BMP ->
    utf16 ToUTF16(unsigned char _high, unsigned char _low)
    {
        SetBits(_high, 5, 7, false);
        SetBits(_low, 6, 7, false);
        return (_high << 6) | _low;
    }

    //the parameters represent UTF-8 character that is part of BMP ->
    utf16 ToUTF16(unsigned char _high, unsigned char _lowa, unsigned char _lowb)
    {
        SetBits(_high, 4, 7, false);
        SetBits(_lowa, 6, 7, false);
        SetBits(_lowb, 6, 7, false);
        return (_high << 12) | (_lowa << 6) | _lowb;
    }

    list<utf8> ToUTF8(CodePoint);

    //returns a single UTF-8 character
    //_codeUnit represent a BMP code point ->
    list<utf8> ToUTF8(utf16 _codeUnit)
    {
        return ToUTF8(static_cast<CodePoint>(_codeUnit));
    }

    CodePoint ToCodePoint(utf16, utf16);
    //returns a single UTF-8 character
    //the parameters represent a valid surrogate pair ->
    list<utf8> ToUTF8(utf16 _highSurrogate, utf16 _lowSurrogate)
    {
        return ToUTF8(ToCodePoint(_highSurrogate, _lowSurrogate));
    }

    //returns a single UTF-8 character
    //_codePoint represent a valid Unicode code point ->
    list<utf8> ToUTF8(CodePoint _codePoint)
    {
        //if the code point must be encoded by one byte
        if (_codePoint < 128)
        {
            return { static_cast<unsigned char>(_codePoint) };
        }
            //if the code point must be encoded by two bytes
        else if (_codePoint >= 128 && _codePoint <= 2047)
        {
            unsigned char high = 0b11000000 | GetBits(_codePoint, 6, 10);
            unsigned char low = 0b10000000 | GetBits(_codePoint, 0, 5);
            return { high, low };
        }
            //if the code point must be encoded by three byte
        else if (_codePoint >= 2048 && _codePoint <= 65535)
        {
            unsigned char high = 0b11100000 | GetBits(_codePoint, 12, 15);
            unsigned char lowa = 0b10000000 | GetBits(_codePoint, 6, 11);
            unsigned char lowb = 0b10000000 | GetBits(_codePoint, 0, 5);
            return { high, lowa, lowb };
        }
            //if the code point must be encoded by four byte
        else if (_codePoint >= 65536)
        {
            unsigned char high = 0b11110000 | GetBits(_codePoint, 18, 20);
            unsigned char lowa = 0b10000000 | GetBits(_codePoint, 12, 17);
            unsigned char lowb = 0b10000000 | GetBits(_codePoint, 6, 11);
            unsigned char lowc = 0b10000000 | GetBits(_codePoint, 0, 5);
            return { high, lowa, lowb, lowc };
        }
    }

    //the parameters represent UTF-8 character that is part of BMP ->
    utf32 ToUTF32(unsigned char _high, unsigned char _lowa)
    {
        SetBits(_high, 5, 7, false);
        SetBits(_lowa, 6, 7, false);
        return (_high << 6) | _lowa;
    }

    //the parameters represent UTF-8 character that is part of BMP ->
    utf32 ToUTF32(unsigned char _high, unsigned char _lowa, unsigned char _lowb)
    {
        SetBits(_high, 4, 7, false);
        SetBits(_lowa, 6, 7, false);
        SetBits(_lowb, 6, 7, false);
        return (_high << 12) | (_lowa << 6) | _lowb;
    }

    //the parameters represent UTF-8 character that is not part of BMP ->
    utf32 ToUTF32(unsigned char _high, unsigned char _lowa, unsigned char _lowb, unsigned char _lowc)
    {
        SetBits(_high, 3, 7, false);
        SetBits(_lowa, 6, 7, false);
        SetBits(_lowb, 6, 7, false);
        SetBits(_lowc, 6, 7, false);
        return (_high << 18) | (_lowa << 12) | (_lowb << 6) | _lowc;
    }

    //the parameters represent a valid surrogate pair ->
    utf32 ToUTF32(utf16 _highSurrogate, utf16 _lowSurrogate)
    {
        utf16 highSurrogateOffset = _highSurrogate - HIGH_SURROGATES_BEGIN;
        utf16 lowSurrogateOffset = _lowSurrogate - LOW_SURROGATES_END;
        return ((highSurrogateOffset << 10) | lowSurrogateOffset) + 65536;
    }

    //the parameters represent UTF-8 character that is part of BMP ->
    CodePoint ToCodePoint(unsigned char _high, unsigned char _lowa)
    {
        return ToUTF32(_high, _lowa);
    }

    //the parameters represent UTF-8 character that is not part of BMP ->
    CodePoint ToCodePoint(unsigned char _high, unsigned char _lowa, unsigned char _lowb)
    {
        return ToUTF32(_high, _lowa, _lowb);
    }

    //the parameters represent a valid UTF-8 sequence ->
    utf32 ToCodePoint(unsigned char _high, unsigned char _lowa, unsigned char _lowb, unsigned char _lowc)
    {
        return ToUTF32(_high, _lowa, _lowb, _lowc);
    }

    //(SYNONYM:ToUTF32)
    //the parameters represent a valid surrogate pair ->
    utf32 ToCodePoint(utf16 _highSurrogate, utf16 _lowSurrogate)
    {
        return ToUTF32(_highSurrogate, _lowSurrogate);
    }
}
