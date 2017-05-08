xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 173;
 13.11456;17.39658;-12.92454;,
 13.11456;17.39658;15.21276;,
 -15.02286;17.39658;15.21276;,
 -15.02286;17.39658;-12.92454;,
 -10.19856;40.70970;10.38846;,
 -10.19856;40.70970;-8.10030;,
 8.29026;40.70970;-8.10030;,
 8.29026;40.70970;10.38846;,
 45.63036;-2.02494;1.14414;,
 22.09344;75.49062;-15.12432;,
 22.09344;75.49062;17.41254;,
 -0.95406;71.15460;1.14414;,
 8.29026;40.70970;10.38846;,
 8.29026;40.70970;-8.10030;,
 -0.95424;-2.02470;-45.44040;,
 -17.22252;75.49062;-21.90342;,
 15.31434;75.49068;-21.90342;,
 8.29026;40.70970;-8.10030;,
 -47.53890;-2.02482;1.14414;,
 -24.00162;75.49074;17.41254;,
 -24.00162;75.49074;-15.12432;,
 -10.19856;40.70970;-8.10030;,
 -10.19856;40.70970;10.38846;,
 -0.95424;-2.02470;47.72862;,
 15.31434;75.49068;24.19164;,
 -17.22252;75.49062;24.19164;,
 8.29026;40.70970;10.38846;,
 -9.44892;95.15221;9.81150;,
 -18.28086;97.36993;-17.28222;,
 -9.27252;96.03901;9.81150;,
 -8.26752;94.15104;5.18298;,
 -2.09838;94.15104;23.20770;,
 -7.79790;96.51187;5.18298;,
 -8.50626;97.88892;9.81150;,
 -15.81720;103.31767;-17.28222;,
 -8.00394;98.64072;9.81150;,
 -2.09838;94.15104;23.20770;,
 -6.46062;98.51323;5.18298;,
 -6.58806;100.05660;9.81150;,
 -11.26500;107.86981;-17.28210;,
 -5.83626;100.55893;9.81150;,
 -2.09838;94.15104;23.20770;,
 -4.45920;99.85057;5.18298;,
 -3.98634;101.32519;9.81150;,
 -5.31726;110.33346;-17.28222;,
 -3.09954;101.50158;9.81150;,
 -2.09838;94.15104;23.20770;,
 -2.09838;100.32012;5.18298;,
 -1.09722;101.50158;9.81150;,
 1.12050;110.33346;-17.28222;,
 -0.21042;101.32519;9.81150;,
 -2.09838;94.15104;23.20770;,
 0.26244;99.85057;5.18298;,
 1.63950;100.55893;9.81150;,
 7.06824;107.86981;-17.28210;,
 2.39130;100.05660;9.81150;,
 -2.09838;94.15104;23.20770;,
 2.26386;98.51323;5.18298;,
 3.80718;98.64072;9.81150;,
 11.62044;103.31767;-17.28222;,
 4.30950;97.88892;9.81150;,
 -2.09838;94.15104;23.20770;,
 3.60114;96.51187;5.18298;,
 5.07576;96.03901;9.81150;,
 14.08410;97.36993;-17.28222;,
 5.25216;95.15221;9.81150;,
 -2.09838;94.15104;23.20770;,
 4.07076;94.15104;5.18298;,
 5.25216;93.14988;9.81150;,
 14.08410;90.93210;-17.28222;,
 5.07576;92.26302;9.81150;,
 -2.09838;94.15104;23.20770;,
 3.60114;91.79023;5.18298;,
 4.30950;90.41316;9.81150;,
 11.62044;84.98442;-17.28210;,
 3.80718;89.66130;9.81150;,
 -2.09838;94.15104;23.20770;,
 2.26386;89.78880;5.18298;,
 2.39130;88.24549;9.81150;,
 7.06824;80.43222;-17.28210;,
 1.63950;87.74310;9.81150;,
 -2.09838;94.15104;23.20770;,
 0.26244;88.45153;5.18298;,
 -0.21042;86.97684;9.81150;,
 1.12050;77.96856;-17.28222;,
 -1.09722;86.80045;9.81150;,
 -2.09838;94.15104;23.20770;,
 -2.09838;87.98191;5.18298;,
 -3.09954;86.80045;9.81150;,
 -5.31726;77.96856;-17.28210;,
 -3.98634;86.97684;9.81150;,
 -2.09838;94.15104;23.20770;,
 -4.45920;88.45153;5.18298;,
 -5.83626;87.74310;9.81150;,
 -11.26500;80.43217;-17.28222;,
 -6.58806;88.24549;9.81150;,
 -2.09838;94.15104;23.20770;,
 -6.46062;89.78880;5.18298;,
 -8.00394;89.66130;9.81150;,
 -15.81720;84.98442;-17.28222;,
 -8.50626;90.41316;9.81150;,
 -2.09838;94.15104;23.20770;,
 -7.79790;91.79023;5.18298;,
 -9.27252;92.26302;9.81150;,
 -18.28086;90.93210;-17.28222;,
 -9.44892;93.14988;9.81150;,
 -2.09838;94.15104;23.20770;,
 -8.26752;94.15104;5.18298;,
 -13.33236;96.38562;-11.61486;,
 -3.90186;94.36554;7.45974;,
 -3.84666;94.64298;7.45974;,
 -2.09838;94.15104;17.15094;,
 -8.26752;94.15104;5.18298;,
 -7.79790;96.51187;5.18298;,
 -11.62212;100.51452;-11.61492;,
 -3.68244;95.03934;7.45974;,
 -3.52530;95.27454;7.45974;,
 -6.46062;98.51323;5.18298;,
 -8.46186;103.67467;-11.61474;,
 -3.22194;95.57796;7.45974;,
 -2.98674;95.73511;7.45974;,
 -4.45920;99.85057;5.18298;,
 -4.33296;105.38502;-11.61486;,
 -2.59032;95.89927;7.45974;,
 -2.31288;95.95447;7.45974;,
 -2.09838;100.32012;5.18298;,
 0.13620;105.38502;-11.61486;,
 -1.88388;95.95447;7.45974;,
 -1.60644;95.89927;7.45974;,
 0.26244;99.85057;5.18298;,
 4.26510;103.67467;-11.61474;,
 -1.21002;95.73511;7.45974;,
 -0.97482;95.57796;7.45974;,
 2.26386;98.51323;5.18298;,
 7.42536;100.51452;-11.61492;,
 -0.67146;95.27454;7.45974;,
 -0.51432;95.03934;7.45974;,
 3.60114;96.51187;5.18298;,
 9.13560;96.38562;-11.61486;,
 -0.35010;94.64298;7.45974;,
 -0.29490;94.36554;7.45974;,
 4.07076;94.15104;5.18298;,
 9.13560;91.91647;-11.61486;,
 -0.29490;93.93649;7.45974;,
 -0.35010;93.65905;7.45974;,
 3.60114;91.79023;5.18298;,
 7.42530;87.78750;-11.61480;,
 -0.51432;93.26269;7.45974;,
 -0.67146;93.02749;7.45974;,
 2.26386;89.78880;5.18298;,
 4.26516;84.62730;-11.61480;,
 -0.97482;92.72413;7.45974;,
 -1.21002;92.56692;7.45974;,
 0.26244;88.45153;5.18298;,
 0.13620;82.91706;-11.61486;,
 -1.60644;92.40276;7.45974;,
 -1.88388;92.34756;7.45974;,
 -2.09838;87.98191;5.18298;,
 -4.33296;82.91706;-11.61480;,
 -2.31288;92.34756;7.45974;,
 -2.59032;92.40276;7.45974;,
 -4.45920;88.45153;5.18298;,
 -8.46192;84.62730;-11.61480;,
 -2.98674;92.56692;7.45974;,
 -3.22194;92.72413;7.45974;,
 -6.46062;89.78880;5.18298;,
 -11.62206;87.78750;-11.61480;,
 -3.52530;93.02749;7.45974;,
 -3.68244;93.26269;7.45974;,
 -7.79790;91.79023;5.18298;,
 -13.33236;91.91647;-11.61486;,
 -3.84666;93.65905;7.45974;,
 -3.90186;93.93654;7.45974;;
 
 149;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;5,6,2,1;,
 4;6,7,3,2;,
 4;7,4,0,3;,
 3;8,9,10;,
 4;11,12,9,8;,
 4;12,13,10,9;,
 4;13,11,8,10;,
 3;14,15,16;,
 4;11,17,15,14;,
 4;17,5,16,15;,
 4;5,11,14,16;,
 3;18,19,20;,
 4;11,21,19,18;,
 4;21,22,20,19;,
 4;22,11,18,20;,
 3;23,24,25;,
 4;11,4,24,23;,
 4;4,26,25,24;,
 4;26,11,23,25;,
 3;27,28,29;,
 4;30,31,28,27;,
 4;31,32,29,28;,
 4;32,30,27,29;,
 3;33,34,35;,
 4;32,36,34,33;,
 4;36,37,35,34;,
 4;37,32,33,35;,
 3;38,39,40;,
 4;37,41,39,38;,
 4;41,42,40,39;,
 4;42,37,38,40;,
 3;43,44,45;,
 4;42,46,44,43;,
 4;46,47,45,44;,
 4;47,42,43,45;,
 3;48,49,50;,
 4;47,51,49,48;,
 4;51,52,50,49;,
 4;52,47,48,50;,
 3;53,54,55;,
 4;52,56,54,53;,
 4;56,57,55,54;,
 4;57,52,53,55;,
 3;58,59,60;,
 4;57,61,59,58;,
 4;61,62,60,59;,
 4;62,57,58,60;,
 3;63,64,65;,
 4;62,66,64,63;,
 4;66,67,65,64;,
 4;67,62,63,65;,
 3;68,69,70;,
 4;67,71,69,68;,
 4;71,72,70,69;,
 4;72,67,68,70;,
 3;73,74,75;,
 4;72,76,74,73;,
 4;76,77,75,74;,
 4;77,72,73,75;,
 3;78,79,80;,
 4;77,81,79,78;,
 4;81,82,80,79;,
 4;82,77,78,80;,
 3;83,84,85;,
 4;82,86,84,83;,
 4;86,87,85,84;,
 4;87,82,83,85;,
 3;88,89,90;,
 4;87,91,89,88;,
 4;91,92,90,89;,
 4;92,87,88,90;,
 3;93,94,95;,
 4;92,96,94,93;,
 4;96,97,95,94;,
 4;97,92,93,95;,
 3;98,99,100;,
 4;97,101,99,98;,
 4;101,102,100,99;,
 4;102,97,98,100;,
 3;103,104,105;,
 4;102,106,104,103;,
 4;106,107,105,104;,
 4;107,102,103,105;,
 3;108,109,110;,
 4;111,112,109,108;,
 4;112,113,110,109;,
 4;113,111,108,110;,
 3;114,115,116;,
 4;111,113,115,114;,
 4;113,117,116,115;,
 4;117,111,114,116;,
 3;118,119,120;,
 4;111,117,119,118;,
 4;117,121,120,119;,
 4;121,111,118,120;,
 3;122,123,124;,
 4;111,121,123,122;,
 4;121,125,124,123;,
 4;125,111,122,124;,
 3;126,127,128;,
 4;111,125,127,126;,
 4;125,129,128,127;,
 4;129,111,126,128;,
 3;130,131,132;,
 4;111,129,131,130;,
 4;129,133,132,131;,
 4;133,111,130,132;,
 3;134,135,136;,
 4;111,133,135,134;,
 4;133,137,136,135;,
 4;137,111,134,136;,
 3;138,139,140;,
 4;111,137,139,138;,
 4;137,141,140,139;,
 4;141,111,138,140;,
 3;142,143,144;,
 4;111,141,143,142;,
 4;141,145,144,143;,
 4;145,111,142,144;,
 3;146,147,148;,
 4;111,145,147,146;,
 4;145,149,148,147;,
 4;149,111,146,148;,
 3;150,151,152;,
 4;111,149,151,150;,
 4;149,153,152,151;,
 4;153,111,150,152;,
 3;154,155,156;,
 4;111,153,155,154;,
 4;153,157,156,155;,
 4;157,111,154,156;,
 3;158,159,160;,
 4;111,157,159,158;,
 4;157,161,160,159;,
 4;161,111,158,160;,
 3;162,163,164;,
 4;111,161,163,162;,
 4;161,165,164,163;,
 4;165,111,162,164;,
 3;166,167,168;,
 4;111,165,167,166;,
 4;165,169,168,167;,
 4;169,111,166,168;,
 3;170,171,172;,
 4;111,169,171,170;,
 4;169,112,172,171;,
 4;112,111,170,172;;
 
 MeshMaterialList {
  2;
  149;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;0.000000;0.168627;1.000000;;
   17.000000;
   0.510000;0.510000;0.510000;;
   0.310000;0.000000;0.052275;;
   TextureFilename {
    "./data/TEXTURE/metal008.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  230;
  0.000000;0.000000;0.000000;,
  0.582050;0.567839;-0.582046;,
  0.000000;-0.707107;-0.707107;,
  0.917325;0.360127;-0.169773;,
  0.917325;0.360128;0.169774;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.923880;-0.382683;,
  0.796276;0.473891;-0.375995;,
  0.796275;0.473891;0.375997;,
  -0.375996;0.473893;-0.796274;,
  0.375997;0.473892;-0.796274;,
  -0.796273;0.473894;0.375997;,
  -0.796274;0.473894;-0.375995;,
  0.375995;0.473893;0.796275;,
  -0.375994;0.473894;0.796275;,
  1.000000;0.000000;0.000000;,
  0.475816;0.562092;-0.676499;,
  -0.940488;0.308082;0.143412;,
  -0.939910;0.292828;-0.175560;,
  -0.894427;0.447214;0.000000;,
  0.475813;0.562092;0.676502;,
  0.000001;0.698317;0.715789;,
  -0.582048;0.567841;-0.582046;,
  -0.976466;-0.215671;0.000000;,
  0.676503;0.562092;-0.475812;,
  -0.475811;0.562094;0.676502;,
  0.894427;0.447214;0.000000;,
  -0.475814;0.562094;-0.676499;,
  -0.981040;-0.173344;-0.086672;,
  -0.676498;0.562096;0.475814;,
  -0.966598;0.247347;-0.067136;,
  -0.987675;0.141386;-0.067137;,
  -0.858385;0.508593;-0.067139;,
  -0.598415;0.798368;-0.067141;,
  -0.247340;0.966600;-0.067139;,
  0.141380;0.987676;-0.067141;,
  0.508590;0.858387;-0.067140;,
  0.798367;0.598417;-0.067137;,
  0.966598;0.247347;-0.067135;,
  0.987676;-0.141382;-0.067134;,
  0.858395;-0.508576;-0.067138;,
  0.598420;-0.798364;-0.067142;,
  0.247343;-0.966599;-0.067144;,
  -0.141394;-0.987674;-0.067139;,
  -0.508602;-0.858380;-0.067139;,
  -0.798373;-0.598408;-0.067138;,
  -0.560690;0.690819;0.456504;,
  0.958312;-0.117042;-0.260652;,
  0.929796;-0.184953;-0.318232;,
  0.788253;-0.526674;-0.318231;,
  0.526678;-0.788251;-0.318230;,
  0.184947;-0.929798;-0.318230;,
  -0.184947;-0.929798;-0.318230;,
  -0.526678;-0.788251;-0.318230;,
  -0.788254;-0.526674;-0.318231;,
  -0.929796;-0.184953;-0.318232;,
  -0.929799;0.184940;-0.318232;,
  -0.788271;0.526647;-0.318231;,
  -0.526724;0.788220;-0.318231;,
  -0.184947;0.929798;-0.318230;,
  0.184947;0.929798;-0.318231;,
  0.526724;0.788220;-0.318231;,
  0.788271;0.526648;-0.318230;,
  0.929799;0.184941;-0.318232;,
  -0.875277;0.174146;0.451180;,
  -0.742052;0.495776;0.451181;,
  -0.495778;0.742052;0.451179;,
  -0.174138;0.875277;0.451182;,
  0.174138;0.875277;0.451182;,
  0.495778;0.742052;0.451179;,
  0.742052;0.495776;0.451181;,
  0.875277;0.174146;0.451180;,
  0.875277;-0.174146;0.451180;,
  0.742052;-0.495776;0.451181;,
  0.495917;-0.741958;0.451182;,
  0.174138;-0.875278;0.451180;,
  -0.174138;-0.875278;0.451181;,
  -0.495917;-0.741958;0.451182;,
  -0.742052;-0.495776;0.451181;,
  -0.875283;-0.174113;0.451180;,
  -0.655534;0.649504;0.385252;,
  -0.884279;0.463360;0.057857;,
  -0.569796;-0.710471;0.412993;,
  -0.994289;-0.089682;0.057858;,
  -0.854189;-0.349200;0.385253;,
  -0.357085;0.850923;0.385253;,
  -0.639655;0.766482;0.057855;,
  -0.952922;0.297645;0.057856;,
  -0.922800;0.004284;0.385255;,
  -0.004262;0.922801;0.385253;,
  -0.297637;0.952925;0.057853;,
  -0.766486;0.639651;0.057854;,
  -0.850925;0.357080;0.385253;,
  0.349204;0.854189;0.385251;,
  0.877300;0.174505;0.447094;,
  0.089692;0.994288;0.057852;,
  -0.463347;0.884286;0.057854;,
  -0.649494;0.655543;0.385254;,
  0.649494;0.655543;0.385254;,
  0.463347;0.884286;0.057856;,
  -0.089692;0.994288;0.057854;,
  -0.349204;0.854189;0.385251;,
  0.850925;0.357080;0.385253;,
  0.766486;0.639651;0.057854;,
  0.297637;0.952925;0.057853;,
  0.004262;0.922801;0.385253;,
  0.922800;0.004284;0.385255;,
  0.952922;0.297645;0.057856;,
  0.639655;0.766482;0.057855;,
  0.357085;0.850923;0.385253;,
  0.854189;-0.349200;0.385253;,
  0.994289;-0.089682;0.057858;,
  0.884279;0.463360;0.057857;,
  0.655534;0.649504;0.385252;,
  0.655531;-0.649507;0.385253;,
  0.352927;-0.846724;0.398123;,
  0.884280;-0.463359;0.057857;,
  0.994289;0.089675;0.057859;,
  0.854195;0.349183;0.385256;,
  0.357087;-0.850922;0.385255;,
  0.639665;-0.766473;0.057858;,
  0.952928;-0.297627;0.057857;,
  0.922800;-0.004270;0.385255;,
  0.004263;-0.922801;0.385253;,
  0.297646;-0.952922;0.057852;,
  0.766486;-0.639650;0.057854;,
  0.850917;-0.357095;0.385257;,
  -0.349198;-0.854190;0.385254;,
  -0.089683;-0.994289;0.057851;,
  0.463357;-0.884282;0.057851;,
  0.649499;-0.655538;0.385253;,
  -0.649496;-0.655540;0.385256;,
  -0.463354;-0.884283;0.057853;,
  0.089681;-0.994289;0.057853;,
  0.349194;-0.854190;0.385256;,
  -0.850916;-0.357098;0.385257;,
  -0.766484;-0.639652;0.057858;,
  -0.297645;-0.952922;0.057857;,
  -0.004260;-0.922801;0.385253;,
  -0.922802;-0.004267;0.385252;,
  -0.952929;-0.297624;0.057853;,
  -0.639664;-0.766475;0.057854;,
  -0.357084;-0.850924;0.385253;,
  -0.854195;0.349183;0.385256;,
  -0.994289;0.089675;0.057859;,
  -0.655531;-0.649507;0.385253;,
  -0.884280;-0.463359;0.057857;,
  0.777708;-0.000002;-0.628626;,
  0.767623;0.160511;-0.620476;,
  0.899314;0.377376;-0.220957;,
  0.718505;-0.297622;-0.628627;,
  0.647758;-0.442066;-0.620474;,
  -0.257916;-0.930410;-0.260418;,
  0.686435;-0.692810;-0.220956;,
  0.770617;-0.145458;-0.620477;,
  0.975272;0.004487;-0.220962;,
  0.549926;-0.549919;-0.628626;,
  0.429290;-0.656291;-0.620477;,
  0.369065;-0.902756;-0.220957;,
  0.656299;-0.429286;-0.620472;,
  0.902764;-0.369050;-0.220951;,
  0.297616;-0.718509;-0.628625;,
  0.145454;-0.770622;-0.620471;,
  -0.004500;-0.975274;-0.220955;,
  0.442060;-0.647760;-0.620476;,
  0.692806;-0.686439;-0.220957;,
  -0.000000;-0.777706;-0.628628;,
  -0.160520;-0.767620;-0.620478;,
  -0.377385;-0.899310;-0.220958;,
  0.160520;-0.767622;-0.620475;,
  0.377385;-0.899310;-0.220958;,
  -0.297616;-0.718510;-0.628624;,
  -0.442060;-0.647762;-0.620474;,
  -0.692806;-0.686439;-0.220957;,
  -0.145454;-0.770622;-0.620471;,
  0.004500;-0.975274;-0.220955;,
  -0.549926;-0.549920;-0.628625;,
  -0.656299;-0.429286;-0.620472;,
  -0.857049;0.449774;-0.251337;,
  -0.902764;-0.369050;-0.220951;,
  -0.429292;-0.656292;-0.620475;,
  -0.369065;-0.902757;-0.220957;,
  -0.718506;-0.297622;-0.628625;,
  -0.770618;-0.145459;-0.620475;,
  -0.975272;0.004487;-0.220962;,
  -0.647759;-0.442067;-0.620472;,
  -0.686435;-0.692810;-0.220956;,
  -0.777708;-0.000002;-0.628625;,
  -0.767625;0.160510;-0.620475;,
  -0.899314;0.377376;-0.220957;,
  -0.767624;-0.160513;-0.620474;,
  -0.899312;-0.377382;-0.220956;,
  -0.718510;0.297614;-0.628625;,
  -0.647762;0.442063;-0.620472;,
  -0.686440;0.692804;-0.220958;,
  -0.770622;0.145445;-0.620474;,
  -0.975274;-0.004509;-0.220955;,
  -0.549932;0.549911;-0.628628;,
  -0.429293;0.656289;-0.620477;,
  -0.369066;0.902756;-0.220957;,
  -0.656306;0.429271;-0.620474;,
  -0.902758;0.369060;-0.220957;,
  -0.297626;0.718502;-0.628628;,
  -0.145467;0.770612;-0.620482;,
  0.300124;0.925663;-0.230379;,
  0.004508;0.975273;-0.220959;,
  -0.442066;0.647759;-0.620472;,
  -0.692811;0.686434;-0.220956;,
  -0.000001;0.777708;-0.628626;,
  0.160511;0.767625;-0.620475;,
  0.377377;0.899314;-0.220957;,
  -0.160513;0.767623;-0.620476;,
  -0.377379;0.899313;-0.220957;,
  0.297629;0.718503;-0.628626;,
  0.442067;0.647757;-0.620474;,
  0.692812;0.686432;-0.220956;,
  0.145471;0.770616;-0.620475;,
  -0.004507;0.975273;-0.220959;,
  0.549933;0.549914;-0.628624;,
  0.656309;0.429277;-0.620468;,
  0.902758;0.369060;-0.220957;,
  0.429293;0.656289;-0.620477;,
  0.369066;0.902756;-0.220957;,
  0.718510;0.297611;-0.628626;,
  0.770622;0.145445;-0.620474;,
  0.975274;-0.004509;-0.220955;,
  0.647763;0.442059;-0.620474;,
  0.686440;0.692804;-0.220958;,
  0.767624;-0.160514;-0.620474;,
  0.899314;-0.377375;-0.220958;;
  149;
  4;5,6,6,5;,
  4;4,3,15,15;,
  4;2,2,6,6;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  3;7,7,8;,
  4;1,16,7,7;,
  4;17,18,19,19;,
  4;20,21,20,8;,
  3;9,9,10;,
  4;22,18,9,9;,
  4;18,23,23,23;,
  4;3,1,24,10;,
  3;11,11,12;,
  4;21,25,11,11;,
  4;3,4,26,26;,
  4;27,22,27,12;,
  3;13,13,14;,
  4;21,4,13,13;,
  4;28,17,28,28;,
  4;17,21,29,14;,
  3;48,48,48;,
  4;30,46,80,81;,
  4;82,31,83,84;,
  4;31,30,81,83;,
  3;49,49,49;,
  4;85,46,85,86;,
  4;46,32,87,88;,
  4;32,31,86,87;,
  3;50,50,50;,
  4;89,46,89,90;,
  4;46,33,91,92;,
  4;33,32,90,91;,
  3;51,51,51;,
  4;93,94,93,95;,
  4;46,34,96,97;,
  4;34,33,95,96;,
  3;52,52,52;,
  4;98,94,98,99;,
  4;46,35,100,101;,
  4;35,34,99,100;,
  3;53,53,53;,
  4;102,94,102,103;,
  4;46,36,104,105;,
  4;36,35,103,104;,
  3;54,54,54;,
  4;106,94,106,107;,
  4;46,37,108,109;,
  4;37,36,107,108;,
  3;55,55,55;,
  4;110,94,110,111;,
  4;94,38,112,113;,
  4;38,37,111,112;,
  3;56,56,56;,
  4;114,115,114,116;,
  4;94,39,117,118;,
  4;39,38,116,117;,
  3;57,57,57;,
  4;119,115,119,120;,
  4;94,40,121,122;,
  4;40,39,120,121;,
  3;58,58,58;,
  4;123,115,123,124;,
  4;94,41,125,126;,
  4;41,40,124,125;,
  3;59,59,59;,
  4;127,82,127,128;,
  4;94,42,129,130;,
  4;42,41,128,129;,
  3;60,60,60;,
  4;131,82,131,132;,
  4;115,43,133,134;,
  4;43,42,132,133;,
  3;61,61,61;,
  4;135,82,135,136;,
  4;82,44,137,138;,
  4;44,43,136,137;,
  3;62,62,62;,
  4;139,46,139,140;,
  4;82,45,141,142;,
  4;45,44,140,141;,
  3;63,63,63;,
  4;143,46,143,144;,
  4;82,145,146,145;,
  4;30,45,144,146;,
  3;64,64,64;,
  4;47,147,148,149;,
  4;147,150,151,148;,
  4;150,152,153,151;,
  3;65,65,65;,
  4;47,150,154,155;,
  4;150,156,157,154;,
  4;156,152,158,157;,
  3;66,66,66;,
  4;47,156,159,160;,
  4;156,161,162,159;,
  4;161,152,163,162;,
  3;67,67,67;,
  4;47,161,164,165;,
  4;161,166,167,164;,
  4;166,152,168,167;,
  3;68,68,68;,
  4;47,166,169,170;,
  4;166,171,172,169;,
  4;171,152,173,172;,
  3;69,69,69;,
  4;152,171,174,175;,
  4;171,176,177,174;,
  4;176,178,179,177;,
  3;70,70,70;,
  4;152,176,180,181;,
  4;176,182,183,180;,
  4;182,178,184,183;,
  3;71,71,71;,
  4;152,182,185,186;,
  4;182,187,188,185;,
  4;187,178,189,188;,
  3;72,72,72;,
  4;152,187,190,191;,
  4;187,192,193,190;,
  4;192,178,194,193;,
  3;73,73,73;,
  4;178,192,195,196;,
  4;192,197,198,195;,
  4;197,178,199,198;,
  3;74,74,74;,
  4;178,197,200,201;,
  4;197,202,203,200;,
  4;202,204,205,203;,
  3;75,75,75;,
  4;178,202,206,207;,
  4;202,208,209,206;,
  4;208,204,210,209;,
  3;76,76,76;,
  4;178,208,211,212;,
  4;208,213,214,211;,
  4;213,204,215,214;,
  3;77,77,77;,
  4;204,213,216,217;,
  4;213,218,219,216;,
  4;218,47,220,219;,
  3;78,78,78;,
  4;204,218,221,222;,
  4;218,223,224,221;,
  4;223,47,225,224;,
  3;79,79,79;,
  4;47,223,226,227;,
  4;223,147,228,226;,
  4;147,47,229,228;;
 }
 MeshTextureCoords {
  173;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.031250;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.031250;0.000000;,
  0.062500;1.000000;,
  0.062500;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;1.000000;,
  0.093750;0.000000;,
  0.187500;1.000000;,
  0.093750;0.000000;,
  0.187500;1.000000;,
  0.187500;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.156250;0.000000;,
  0.312500;1.000000;,
  0.156250;0.000000;,
  0.312500;1.000000;,
  0.312500;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.218750;0.000000;,
  0.437500;1.000000;,
  0.218750;0.000000;,
  0.437500;1.000000;,
  0.437500;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.281250;0.000000;,
  0.562500;1.000000;,
  0.281250;0.000000;,
  0.562500;1.000000;,
  0.562500;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.343750;0.000000;,
  0.687500;1.000000;,
  0.343750;0.000000;,
  0.687500;1.000000;,
  0.687500;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.406250;0.000000;,
  0.812500;1.000000;,
  0.406250;0.000000;,
  0.812500;1.000000;,
  0.812500;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.468750;0.000000;,
  0.937500;1.000000;,
  0.468750;0.000000;,
  0.937500;1.000000;,
  0.937500;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
 MeshVertexColors {
  173;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;,
  120;1.000000;1.000000;1.000000;1.000000;,
  121;1.000000;1.000000;1.000000;1.000000;,
  122;1.000000;1.000000;1.000000;1.000000;,
  123;1.000000;1.000000;1.000000;1.000000;,
  124;1.000000;1.000000;1.000000;1.000000;,
  125;1.000000;1.000000;1.000000;1.000000;,
  126;1.000000;1.000000;1.000000;1.000000;,
  127;1.000000;1.000000;1.000000;1.000000;,
  128;1.000000;1.000000;1.000000;1.000000;,
  129;1.000000;1.000000;1.000000;1.000000;,
  130;1.000000;1.000000;1.000000;1.000000;,
  131;1.000000;1.000000;1.000000;1.000000;,
  132;1.000000;1.000000;1.000000;1.000000;,
  133;1.000000;1.000000;1.000000;1.000000;,
  134;1.000000;1.000000;1.000000;1.000000;,
  135;1.000000;1.000000;1.000000;1.000000;,
  136;1.000000;1.000000;1.000000;1.000000;,
  137;1.000000;1.000000;1.000000;1.000000;,
  138;1.000000;1.000000;1.000000;1.000000;,
  139;1.000000;1.000000;1.000000;1.000000;,
  140;1.000000;1.000000;1.000000;1.000000;,
  141;1.000000;1.000000;1.000000;1.000000;,
  142;1.000000;1.000000;1.000000;1.000000;,
  143;1.000000;1.000000;1.000000;1.000000;,
  144;1.000000;1.000000;1.000000;1.000000;,
  145;1.000000;1.000000;1.000000;1.000000;,
  146;1.000000;1.000000;1.000000;1.000000;,
  147;1.000000;1.000000;1.000000;1.000000;,
  148;1.000000;1.000000;1.000000;1.000000;,
  149;1.000000;1.000000;1.000000;1.000000;,
  150;1.000000;1.000000;1.000000;1.000000;,
  151;1.000000;1.000000;1.000000;1.000000;,
  152;1.000000;1.000000;1.000000;1.000000;,
  153;1.000000;1.000000;1.000000;1.000000;,
  154;1.000000;1.000000;1.000000;1.000000;,
  155;1.000000;1.000000;1.000000;1.000000;,
  156;1.000000;1.000000;1.000000;1.000000;,
  157;1.000000;1.000000;1.000000;1.000000;,
  158;1.000000;1.000000;1.000000;1.000000;,
  159;1.000000;1.000000;1.000000;1.000000;,
  160;1.000000;1.000000;1.000000;1.000000;,
  161;1.000000;1.000000;1.000000;1.000000;,
  162;1.000000;1.000000;1.000000;1.000000;,
  163;1.000000;1.000000;1.000000;1.000000;,
  164;1.000000;1.000000;1.000000;1.000000;,
  165;1.000000;1.000000;1.000000;1.000000;,
  166;1.000000;1.000000;1.000000;1.000000;,
  167;1.000000;1.000000;1.000000;1.000000;,
  168;1.000000;1.000000;1.000000;1.000000;,
  169;1.000000;1.000000;1.000000;1.000000;,
  170;1.000000;1.000000;1.000000;1.000000;,
  171;1.000000;1.000000;1.000000;1.000000;,
  172;1.000000;1.000000;1.000000;1.000000;;
 }
}
