
BINARRAY : BINARIZE AN ARRAY

usage:
	java BinArray -d <outdir> arrayFile
	outdir    : output directory for the array data
	arrayFile : file which contains the array to binarize (java style)
	
	note that array with dimension > 3 will fail (eg [][][][])
	those are definitely not recommanded anyway
	
	note that it only handles int, short and byte array
	String array are not handled
	
arrayFile is a text file which contain array define as in java
ex:
	int[] data = { 12, 13, 5, 8, 123};
	byte data2[][] = {{1}, {2, 7, 8, 9}};
	short[][]val[] = {
		{ {-1}, {0,5,8} },
		{ {12, -4}, {4} },
		{ {32767, -1},  {-1}, {-7, 8, 32} }
	};
	

in code, you can then read those by doing
// open the pack which contain your array
pack_open(DATA.PACK_ARRAY);

// load the array
int[] data = (int[]) pack_readArray(DATA.ARRAY_DATA);	
byte data2[][] = (byte [][]) pack_readArray(DATA.ARRAY_DATA2);
short[][][] val = (short[][][]) pack_readArray(DATA.ARRAY_VAL);

// close the pack
pack_close();

