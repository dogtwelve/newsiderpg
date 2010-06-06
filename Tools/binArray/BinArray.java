

////////////////////////////////////////////////////////////////////////////////
// this script binarize  arrays from array define in source file like format
//	int[] data = { 12, 13, 5, 8, 123};
//	byte data2[][] = {{1},  {2, 7, 8, 9} };
//	short[][][] val = {
//		{ {-1}, {0,5,8}	},
//		{ {12, -4}, {4}	},
//		{ {32767, -1}, {-1}, {-7, 8, 32} }
//	};
////////////////////////////////////////////////////////////////////////////////
import java.util.*;
import java.io.*;
import java.lang.*;
import java.lang.reflect.Array;

class BinStream extends ByteArrayOutputStream
{
	boolean bigEndian = false;

   // --- write32BigEndian
	void write32BigEndian(int value) throws Exception
	{
		write((byte)((value >> 24) & 0xFF));
		write((byte)((value >> 16) & 0xFF));
		write((byte)((value >> 8) & 0xFF));
		write((byte)(value & 0xFF));
	}

	// --- write16BigEndian
	void write16BigEndian(int value) throws Exception
	{
		write((byte)((value >> 8) & 0xFF));
		write((byte)(value & 0xFF));
	}
			
	// --- write32LittleEndian
	void write32LittleEndian(int value) throws Exception
	{
		write((byte)(value & 0xFF));
		write((byte)((value >> 8) & 0xFF));
		write((byte)((value >> 16) & 0xFF));
		write((byte)((value >> 24) & 0xFF));
	}
			
	// --- write16LittleEndian
	void write16LittleEndian(int value) throws Exception
	{
		write((byte)(value & 0xFF));
		write((byte)((value >> 8) & 0xFF));
	}
	
	// --- write32
	void write32(int value) throws Exception
	{
		if (bigEndian)
			write32BigEndian(value);
		else
			write32LittleEndian(value);
	}
			
	// --- write16
	void write16(int value) throws Exception
	{
		if (bigEndian)
			write16BigEndian(value);
		else
			write16LittleEndian(value);
	}		
};



class BinArray
{
	// --- Dbg
    static void Dbg(String a)
    {
        System.out.println(a);
    }
            
    // --- ERR
    static void ERR(String a)
    {
    	System.err.println("ERR::"+a);
    }
    
	
	static String getPath(String path) throws Exception
	{
		File dir = new File(path);
		return dir.getAbsolutePath();
	}

	static public void main(String[] args)
	{
	    try 
		{
	        BinArray m = new BinArray();
	        m.exec(args);
	    }
		catch(Exception e)
	    { 
	    	Dbg("error while executing :"+e);
		}
	}
	
	
	
	
	
	
	
/*
int[] data1 = 
{
	12, 13, 5, 8, 123
};
byte data2[][] = 
{
	{1}, 
	{2, 7, 8, 9}
};
short[][]data3[] = {
	{
		{-1},
		{0,5,8}
	},
	{
		{12, -4},
		{4}
	},
	{
		{32767, -1}, 
		{-1}, 
		{-7, 8, 32}
	}
};
*/
	
	static boolean verbose = false;
	void exec(String[] args)
	{
		try
		{
			if (args.length == 0)
			{
				Dbg("usage:");
				Dbg("    java BinArray -d <outdir> arrayFile");
				Dbg("      outdir    : output directory for the array data");
				Dbg("      arrayFile : file which contains the array to binarize (java style)");
				Dbg("      -v        : verbose mode");
				Dbg("note that array with dimension > 3 will fail (eg [][][][])");
				Dbg("those are definitely not recommanded anyway");
				return;
			}

			String filename = null;
			String outDirectory = ".\\";
			for (int i=0; i<args.length; i++) 
			{
				if ((args[i].compareToIgnoreCase("-d") == 0) && (i+1<args.length)) 
				{
					outDirectory = args[i+1];
					outDirectory = getPath(outDirectory);
					i++;			
				}
				else if (args[i].compareToIgnoreCase("-v") == 0) 
				{
					verbose = true;
				}
				else  
				{
					filename = new String(args[i]);
					filename = getPath(filename);
				}
			}

			if (filename != null) 
			{
				parse(filename, outDirectory);
			}
			else 
			{
				ERR("no data file to parse");
			}
/*
			Dbg("data1");
			binarize("data", data1, ".");
			
			Dbg("data2");
			binarize("data2", data2, ".");
			
			Dbg("val");
			binarize("val", data3, ".");
*/
		}
		catch (Exception e)
		{
			Dbg("ERROR::"+e);
		}
	}

	static int parseArrayGoodType = 0;

	static final private int ARRAY_BYTE = 0;
	static final private int ARRAY_SHORT = 1;
	static final private int ARRAY_INT = 2;
	/// get type of array
	static int getType(Object array) throws Exception
	{
		String name = array.getClass().getName();
		int idx = name.lastIndexOf("[");
		if (idx >= 0)
		{
			name = name.substring(idx+1, name.length());
		}
//		Dbg("class name :"+name);

		if (name.startsWith("B")) // byte
		{
			return ARRAY_BYTE;
		}
		else if (name.startsWith("S")) // short
		{
			return ARRAY_SHORT;
		}
		else if (name.startsWith("I")) // int
		{
			return ARRAY_INT;
		}
		else if (name.startsWith("Ljava.lang.Object"))
		{
			if (array.getClass().isArray())
			{
				return getType(Array.get(array, 0));
			}
			else
			{
				ERR("type of array not handled (only int, short or byte)");
				System.exit(1);
			}
		}
		else 
		{
			ERR("type of array not handled (only int, short or byte)");
			System.exit(1);
		}
		return -1;
	}
	
	/// bnarize an array
	static void binarize(String arrayName, Object array, String outDirectory) throws Exception
	{
		BinStream os = new BinStream();
		
		// binarize the array
		parseArray(os, array) ;
		
		// get binary data of array
		byte[] data = os.toByteArray();

		// write array in file
		FileOutputStream fd_dataOut = null;
		String outfileName = (getPath(outDirectory) + "\\" + arrayName+".array").toUpperCase();
		try 
		{
			fd_dataOut = new FileOutputStream(outfileName);
		} 
		catch(Exception e) 
		{
			ERR("fatal error, cannot create output file: "+outfileName);
			System.exit(1);
		}
		if (fd_dataOut == null) 
		{
			ERR("fatal error, cannot create output file: "+outfileName);
			System.exit(1);
		}
		// write array to disk
		fd_dataOut.write(data);
		fd_dataOut.close();
	}
	
	static int getArrayDimension(Object array)
	{
		if (! array.getClass().isArray())
			return 0;
		return 1 + getArrayDimension(Array.get(array, 0));
	}
	
	
	/// recursive function to parse an array to a byte buffer (binStream)
	static void parseArray(BinStream os, Object array) throws Exception
	{
		if (! array.getClass().isArray())
		{
			ERR("not an array");
			return;
		}

		int nbData = Array.getLength(array);
		Object elem = Array.get(array, 0);
		int type = getType(array);

		// is it a multiarray?
		if (elem.getClass().isArray())
		{
			int dim = getArrayDimension(array);
			if (dim > 3)
			{
				ERR("array with dimension biggger than 3 (eg [][][]) are not supported");
				System.exit(1);
			}
			os.write(
					(dim <<4)					// array dimension
				|	(((nbData>0xFF)?1:0)<<3) 	// nb data padding
				|	(1<<2)						// multiarray
				|	(type)						// data type
				);

			// write nb of subArray
			if (nbData > 0xFFFF)
			{
				ERR("array contain more than "+0xFFFF+" subArray, unable to process");
				System.exit(1);
			}
			else if (nbData > 0xFF)
			{
				os.write16((short)(nbData&0xFFFF));
			}
			else
			{
				os.write((byte)(nbData&0xFF));
			}

			for (int i=0; i<nbData; i++)
			{
				parseArray(os, Array.get(array, i));
			}
		}
		else
		{
			//get smallest padding
			int[] tmpbuf = new int[nbData];
			int dataPadding = ARRAY_BYTE;
			for (int i=0; i<nbData; i++)
			{
				tmpbuf[i] = Array.getInt(array, i);
				if ( (((tmpbuf[i] < -128) || tmpbuf[i] > 127)) && (dataPadding == ARRAY_BYTE) )
				{
					dataPadding = ARRAY_SHORT;
					if (parseArrayGoodType < 1)
						parseArrayGoodType = 1;
				}
				if (((tmpbuf[i] < -32768) || (tmpbuf[i] > 32767)) && (dataPadding == ARRAY_SHORT))
				{
					dataPadding = ARRAY_INT;
					if (parseArrayGoodType < 2)
						parseArrayGoodType = 2;
				}
				if (dataPadding > type)
				{
					ERR("error in array, a value exceed its type boundaries : "+(int)tmpbuf[i]);
					System.exit(1);
				}
			}

			os.write(
					(dataPadding<<4)			// real data padding
				|	(((nbData>0xFF)?1:0)<<3) 	// nb data padding
				|	(0<<2)						//not  multiarray
				|	(type)						// data type
				);
			if (nbData > 0xFF)
				os.write16((short)(nbData&0xFFFF));
			else
				os.write((byte)(nbData&0xFF));
			// write data
			for (int i=0; i<nbData; i++)
			{
				if (dataPadding == ARRAY_BYTE)
				{
					os.write((byte)(tmpbuf[i] & 0xFF));
				}
				else if (dataPadding == ARRAY_SHORT)
				{
					os.write16((short)(tmpbuf[i] & 0xFFFF));
				}
				else
				{
					os.write32(tmpbuf[i]);
				}
			}
		}
	}

	



	static String getFileAsString(String filename) throws Exception
	{
		FileReader in = new FileReader(filename);
		String file ="";
		while (in.ready())
		{
			file += (char)in.read();
		}
		in.close();
		return file;
	}
	
	static String removeComment(String stin) throws Exception
	{
		int idx;
		// remove // comment
		while((idx = stin.indexOf("//")) >= 0)
		{
			stin = stin.substring(0,idx) + stin.substring(stin.indexOf("\n", idx), stin.length());
		}

		// remove / * ...  * / comment
		while((idx = stin.indexOf("/*")) >= 0)
		{
			stin = stin.substring(0,idx) + stin.substring(stin.indexOf("*/", idx), stin.length());
		}
		return stin;
	}
	
	static String removeString(String in, String remove) throws Exception
	{
		int idx;
		int len = remove.length();
		while((idx = in.indexOf(remove)) >= 0)
		{
			in = in.substring(0, idx) + in.substring(idx+len, in.length());
		}
		return in;
	}

	/// parse an array file to binarize it
	void parse(String inFile, String outDirectory) throws Exception
	{
		int idx;
		boolean issueWarning = false;
		try 
		{
			// get whole file as a string, then clean it
			String file = getFileAsString(inFile);
			file = removeComment(file);
			file = removeString(file, "\t");
			file = removeString(file, "\n");
			file = removeString(file, "\r");
			file = file.trim();

			String decl, value;
			// read file
			while (true)
			{
				idx = file.indexOf("=");
				if (idx < 0)
					break;
				decl = file.substring(0, idx).trim();
				file = file.substring(idx+"=".length(), file.length()).trim();

				idx = file.indexOf(";");
				if (idx < 0) //<-- should never happen, if it does, this should be a syntax error -> look for final "}"
					idx = file.lastIndexOf("}");

				value = file.substring(0, idx).trim();
				file = file.substring(idx+"=".length(), file.length()).trim();
				
				// get array dim
				int dim = 0;
				while (true)
				{
					idx = decl.indexOf("[]");
					if (idx >= 0)
					{
						dim++;
						decl = decl.substring(0, idx) + " " + decl.substring(idx+2, decl.length());
					}
					else
					{
						break;
					}
				}
				if (dim == 0)
					continue;



				// get array type, name,
				decl = decl.trim();
				idx = decl.indexOf(" ");
				if (idx < 0)
				{
					ERR("error while parsing");
					return;
				}
				String typeStr = decl.substring(0,idx).trim();
				int type = -1;
				if (typeStr.indexOf("byte") == 0)
					type = ARRAY_BYTE;
				else if (typeStr.indexOf("short") == 0)
					type = ARRAY_SHORT;
				else if (typeStr.indexOf("int") == 0)
					type = ARRAY_INT;
				String arrayName = decl.substring(idx+1, decl.length()).trim();
				
				// get the array
				Object array = getArray(type, value);
				
				// binarize the array
				binarize(arrayName, array, outDirectory);
			}
			if (issueWarning)
			{
				Dbg("    you have some multidimensional array");
				Dbg("    --> did you know that [] array are faster ?");
			}

		} 
		catch(Exception e)
		{
			ERR("error while parsing/processing :: "+e);
		}
		// close files
//		fileClose();
	}
	
	/// split an array string , take care of the nesting 
	static String[] split(String value)
	{
//		Dbg("value:"+value);
		if (value.indexOf("{") < 0)
		{
			return value.split(",");
		}
		
		Vector vec = new Vector();
		int nesting = 0;
		int curIdx = 0;
		
		while (curIdx < value.length())
		{
			if (value.charAt(curIdx) == '{')
			{
				nesting++;
			}
			if (value.charAt(curIdx) == '}')
			{
				nesting--;
			}
			if (	(value.charAt(curIdx) == ',')
				&&	(nesting == 0)
				)
			{
				String a = value.substring(0, curIdx).trim();
//Dbg("->"+a);
				vec.add(a);
				value = value.substring(curIdx+1, value.length()).trim();
//Dbg("  "+value);
				curIdx = 0;
			}
			else
				curIdx++;
		}
		// add remaining
		if (! value.equals("")) // could happen if array ends with a ","
			vec.add(value);
		
		// convert to String array
		int nb = vec.size();
		String[] data = new String[nb];
		for (int i=0; i<nb; i++)
		{
			data[i] = (String) vec.elementAt(i);
//Dbg(">"+data[i]);
		}

		return data;
	}

	/// get an array from an array string
	Object getArray(int type, String value)
	{
		Object array = null;

		// remove { and }
		value = value.substring(value.indexOf("{")+1, value.lastIndexOf("}")).trim();
		
		// split in multiple array
		String[] data = split(value);
		int nbData = data.length;

		//check multiarray
		if (value.indexOf("{") >= 0)
		{
			// create array
			Object[] data1 = new Object[nbData];
			array = (Object) data1;

			// fill array
			for (int i=0; i<nbData; i++)
			{
				Object child = getArray(type, data[i]);
				Array.set(array, i, child); 
			}
		}
		else
		{
			// create array
			switch(type)
			{
				case ARRAY_BYTE:
				{
					byte[]data2 = new byte[nbData];
					array = (Object) data2;
				}
				break;
				case ARRAY_SHORT:
				{
					short[]data3 = new short[nbData];
					array = (Object) data3;
				}
				break;
				case ARRAY_INT:
				{
					int[]data4 = new int[nbData];
					array = (Object) data4;
				}
				break;
			}
			// fill array
			for (int i=0; i<nbData; i++)
			{
				int val = Integer.valueOf(data[i].trim()).intValue();
				
				switch(type)
				{
					case ARRAY_BYTE:
					{
						Array.setByte(array, i, (byte)val);
					}
					break;
					case ARRAY_SHORT:
					{
						Array.setShort(array, i, (short)val);
					}
					break;
					case ARRAY_INT:
					{
						Array.setInt(array, i, val);
					}
					break;
				}
			}
		}

		return array;
	}
	
	
	
	
	/*
	
	static void binarizeArray(String arrayName, String array, int type, int dimension) throws Exception
	{
		// clean the string
		array = removeString(array, "\t");
		array = removeString(array, "\n");
		array = removeString(array, "\r");
		array = array.trim();
		
		// parse the string
		BinStream os = new BinStream();
		parseArray(os, array, type, dimension);
		
		// get binary data of array
		byte[] data = os.toByteArray();
		
		// write array in file
		FileOutputStream fd_dataOut = null;
		String outfileName = outDir + "\\" + arrayName+".array";
		try 
		{
			fd_dataOut = new FileOutputStream(outfileName.toUpperCase());
		} 
		catch(Exception e2) 
		{
			ERR("fatal error, cannot create output file:"+outfileName);
			System.exit(1);
		}
		if (fd_dataOut == null) 
		{
			ERR("fatal error, cannot create output file:"+outfileName);
			System.exit(1);
		}
		// write array to disk
		fd_dataOut.write(data);
		fd_dataOut.close();
	}
	
	static int getDimension(Object array)
	{
		String name = array.getClass().getName();
		int dim = 0;
		int idx = 0;
		int tmp = 0;
		while ((tmp = name.indexOf("[", idx)) >= 0)
		{
			dim++;
			idx = tmp+1;
		}
		return dim;
	}
	
	static StringBuffer convertArray(Object array) throws Exception
	{
		StringBuffer out = new StringBuffer("");
		String name = array.getClass().getName();
		
		int dim = getDimension(array);

		out.append("{");
		if (dim > 1)
		{
			for (int i=0; i<java.lang.reflect.Array.getLength(array); i++)
			{
				Object obj = java.lang.reflect.Array.get(array, i);
				out.append(convertArray(obj));
				out.append(",");
			}
		}
		else
		{
			if (name.indexOf("I") >= 0) // int
			{
				for (int i=0; i<java.lang.reflect.Array.getLength(array); i++)
				{
					out.append(java.lang.reflect.Array.getInt(array, i));
					out.append(",");
				}
			}
			else if (name.indexOf("B") >= 0) // byte
			{
				for (int i=0; i<java.lang.reflect.Array.getLength(array); i++)
				{
					out.append(java.lang.reflect.Array.getByte(array, i));
					out.append(",");
				}
			}
			else if (name.indexOf("S") >= 0) // short
			{
				for (int i=0; i<java.lang.reflect.Array.getLength(array); i++)
				{
					out.append(java.lang.reflect.Array.getShort(array, i));
					out.append(",");
				}
			}
		}
		out.append("}");
		return out;
	}
	
	
	
	static void parseArray(BinStream os, String value, int type, int arrayDim) throws Exception
	{
//Dbg("---" + value);
		if (arrayDim > 3)
		{
			ERR("ERROR too many dimension to array, cannot process");
			System.exit(1);
		}
		
		int idx0 = value.indexOf("{");
		int idx1 = value.lastIndexOf("}");

		if (idx0<0 || idx1<0)
		{
			ERR("error while parsing values");
			System.exit(1);
		}
		value = value.substring(idx0+1, idx1).trim();
		idx0 = value.indexOf("{");
		
		//String[] data = value.split(",");
//Dbg("->"+value);
		String[] data = split(value);
		int nbData = data.length;
//Dbg("nb value:"+nbData);
// for (int k=0; k<nbData; k++)
	// Dbg(k+"::"+data[k]);
		// multiarray
		if (idx0 >= 0)
		{
			os.write(
					(arrayDim<<4)	// real data padding not relevant for multiarray
				|	(((nbData>0xFF)?1:0)<<3) // nb data padding
				|	(1<<2)	// multiarray
				|	(type)	// data type
				);
			if (nbData > 0xFF)
				os.write16((short)(nbData&0xFFFF));
			else
				os.write((byte)(nbData&0xFF));
		
			for (int i=0; i<nbData; i++)
			{
				parseArray(os, data[i], type, arrayDim-1);
			}
		}
		else
		{
// check if last data is empty, could hapen if array ends with a ","
// if (data[nbData-1].trim() == "")
// {
	// nbData--;
// }
			int[] tmpbuf = new int[nbData];
			int dataPadding = ARRAY_BYTE;
			for (int i=0; i<nbData; i++)
			{
				Integer d = Integer.valueOf(data[i].trim());
				tmpbuf[i] = d.intValue();

				if ((((tmpbuf[i] < -128) || tmpbuf[i] > 127)) && (dataPadding == ARRAY_BYTE))
				{
					dataPadding = ARRAY_SHORT;
					if (parseArrayGoodType < 1)
						parseArrayGoodType = 1;
				}
				if (((tmpbuf[i] < -32768) || (tmpbuf[i] > 32767)) && (dataPadding == ARRAY_SHORT))
				{
					dataPadding = ARRAY_INT;
					if (parseArrayGoodType < 2)
						parseArrayGoodType = 2;
				}
				if (dataPadding > type)
				{
					ERR("error in array, a value exceed its type boundaries : "+(int)tmpbuf[i]);
					System.exit(1);
				}
				
//				vec.add(d);
			}
			
			os.write(
					(dataPadding<<4)	// real data padding
				|	(((nbData>0xFF)?1:0)<<3) // nb data padding
				|	(0<<2)	//not  multiarray
				|	(type)	// data type
				);
			if (nbData > 0xFF)
				os.write16((short)(nbData&0xFFFF));
			else
				os.write((byte)(nbData&0xFF));

			for (int i=0; i<nbData; i++)
			{
				if (dataPadding == ARRAY_BYTE)
				{
					os.write((byte)(tmpbuf[i] & 0xFF));
				}
				else if (dataPadding == ARRAY_SHORT)
				{
					os.write16((short)(tmpbuf[i] & 0xFFFF));
				}
				else
				{
					os.write32(tmpbuf[i]);
				}
			}
			
		}
	}
	
*/
	

	
	

	
	
}