
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


import java.util.*;
import java.io.*;
import java.lang.*;
import java.util.zip.*;


class ExportText
{
    // --- verbose
	boolean verbose = false;
	boolean bigEndian = false;

            
    // --- LOG
    static void LOG(String a)
    {
        System.out.println(a);
    }
            
    // --- ERR
    static void ERR(String a)
    {
    	System.err.println("ERR::"+a);
    }
			
    // --- ASSERT
	static void ASSERT(boolean cond, String a) throws Exception
    {
        if (cond) 
        {
            ERR(a);
            throw new Exception(a);
        }
    }

    // --- write32BigEndian
	void write32BigEndian(FileOutputStream out, int value) throws Exception
    {
		byte [] b = new byte[4];
		b[0] = (byte)((value >> 24) & 0xFF);
		b[1] = (byte)((value >> 16) & 0xFF);
		b[2] = (byte)((value >> 8) & 0xFF);
		b[3] = (byte)(value & 0xFF);
		out.write(b, 0, 4);
	}
    
    // --- write16BigEndian
	void write16BigEndian(FileOutputStream out, int value) throws Exception
	{
		byte [] b = new byte[2];
		b[0] = (byte)((value >> 8) & 0xFF);
		b[1] = (byte)(value & 0xFF);
		out.write(b, 0, 2);
	}
			
	// --- write32LittleEndian
	void write32LittleEndian(FileOutputStream out, int value) throws Exception
	{
		byte [] b = new byte[4];
		b[0] = (byte)(value & 0xFF);
		b[1] = (byte)((value >> 8) & 0xFF);
		b[2] = (byte)((value >> 16) & 0xFF);
		b[3] = (byte)((value >> 24) & 0xFF);
		out.write(b, 0, 4);
	}
			
    // --- write16LittleEndian
	void write16LittleEndian(FileOutputStream out, int value) throws Exception
	{
		byte [] b = new byte[2];
		b[0] = (byte)(value & 0xFF);
		b[1] = (byte)((value >> 8) & 0xFF);
		out.write(b, 0, 2);
	}
	
	// --- write32
	void write32(FileOutputStream out, int value) throws Exception
	{
        if (bigEndian)
            write32BigEndian(out, value);
		else
			write32LittleEndian(out, value);
	}
			
	// --- write16
	void write16(FileOutputStream out, int value) throws Exception
	{
		if (bigEndian)
            write16BigEndian(out, value);
		else
				write16LittleEndian(out, value);
	}















	// get filepath given complete filename
	String getFilePath(String filename) throws Exception
	{
		int i;
		if ( (i = filename.lastIndexOf('\\')) != -1) 
		{
			return filename.substring(0, i) + "\\";

		} 
		else if ( (i = filename.lastIndexOf('/')) != -1) 
		{
			filename = filename.substring(0, i) + "/";
			filename = filename.replaceAll("\\", "/");
			return filename;
		}
		else 
		{
			return ".\\";
		}
	}

	void createDirectoryIfNotExist(String path) throws Exception
	{
		File dir = new File(path);
		if (dir.exists()) 
		{
			if (! dir.isDirectory())
			{
				ERR(path+" already exist and is not a directory");
				throw new Exception(path+" already exist and is not a directory");
			}
		}
		else 
		{
			dir.mkdir();
		}
	}

	static FileWriter fd_defineJava;
//	static FileWriter fd_java;

	void writeTemplete(String name, String sprdat, String id, String viewimg, String param1, String param2, String param3, String param4, String param5) throws Exception
	{
		fd_defineJava.write("TEMPLATE OBJECT_LAYER " + "\"" + name.toUpperCase() + "\"\n");
		fd_defineJava.write("{\n");
		fd_defineJava.write("      ID     " + id.toUpperCase() + "\n");
		fd_defineJava.write("      SPRITE " + "\"" + sprdat.toUpperCase() + "\"");
		fd_defineJava.write("\n");
		fd_defineJava.write("      SET SPRITE 0\n");
		fd_defineJava.write("      SET MODULE -1\n");
		fd_defineJava.write("      SET FRAME\t" + viewimg.toUpperCase() + "\n");
		fd_defineJava.write("\n");
		fd_defineJava.write("\n");
		fd_defineJava.write("      PARAMS\n");
		fd_defineJava.write("      {\n");
		fd_defineJava.write("            " + param1.toUpperCase() + "\t" + "\"NOT FIX\" \"VIEW TOOL IDX\"\n");
		fd_defineJava.write("            " + param2.toUpperCase() + "\t" + "\"NOT FIX\" \"STATIC VALUE\"\n");
		fd_defineJava.write("            " + param3.toUpperCase() + "\t" + "\"ANI TYPE\" \"0:FRAME, 1:ANI\"\n");
		fd_defineJava.write("            " + param4.toUpperCase() + "\t" + "\"DRAW IDX\" \"ANI OR FRAME IDX\"\n");
		fd_defineJava.write("            " + param5.toUpperCase() + "\t" + "\"NOT USE\" \"\"\n");
		fd_defineJava.write("      }\n");
		fd_defineJava.write("}\n\n");
	}

	void openFile () throws Exception
	{
		headerDir = getFilePath(headerDir);

		fd_defineJava = new FileWriter(headerDir+"map.gts");

//		writeTemplete("nams", ".\\..\\..\\gfx\\sprites\\background\\map_5.sprite", 621, 21, 20,0,0,20,0);
	}

	void closeFile () throws Exception
	{
		fd_defineJava.close();
	}
	
	void defineSheet (String sheetname) throws Exception
	{
		sheetname = sheetname.toUpperCase();
		fd_defineJava.write("//------------------------------------------------------------------------- "+sheetname+"\n");
//		fd_java.write("//------------------------------------------------------------------------- "+sheetname+"\n");
	}

	void defineString (String id, int nb) throws Exception
	{
		id = id.toUpperCase();
		fd_defineJava.write("#define "+id+" \t\t\t "+nb+"\n");
//		fd_java.write("\tfinal static int "+id+" \t\t\t= "+nb+";\n");
	}

	
	
	void readFully(InputStream in, byte[] b) throws Exception
	{
		int off = 0;
		int len = b.length;
		int rd;
		while (len > 0)
		{
			rd = in.read(b, off, len);
			off += rd;
			len -= rd;
		}
	}
	
	int getInt (Hashtable table, int key) throws Exception
	{
		Integer i = (Integer) table.get(new Integer(key));
		return i.intValue();
	}
	
	void parse (String filename) throws Exception
	{
		StringBuffer log = new StringBuffer("");
		String logName = filename+".log";
		StringBuffer warning = new StringBuffer("");

		//LOG("    parsing "+filename);
		FileInputStream fi = new FileInputStream(filename);
		if (fi == null)
		{
			LOG("ERROR:: cannot find file "+filename);
			System.exit(1);
		}

		ZipInputStream zip = new ZipInputStream(fi);
		ZipEntry ze = null;
		do 
		{
			ze = zip.getNextEntry();
			//LOG(ze.getName());
		}
		while(! ze.getName().equals("content.xml"));

		// parse all sheet in the document
		ODSXmlParser parser = new ODSXmlParser();
		WorkSheet[] wkSheet;
		wkSheet = parser.parse(zip);

		// create header file
		openFile();
		
//		System.out.print("    ");
		WorkSheet acurSheet = wkSheet[0];

//		System.out.print("\n");
//		System.out.print("length>>" + wkSheet.length + "\n");
//		System.out.print("nbRow>>" + acurSheet.nbRow + "\n");
//		System.out.print("nbCell>>" + acurSheet.nbCell + "\n");

		for (int i = 0; i < wkSheet.length; i++)
		{
			// alias for current sheet
			WorkSheet curSheet = wkSheet[i];

			System.out.print(".");
			int curOffset = 0;

			// get sheetName
			//sheetName = curSheet.name.toUpperCase();

			String[] lang = new String[255];
//			int nbLang = 0;
//			int firstRow = 0;
			Hashtable hash = new Hashtable();

			String str[] = new String[curSheet.nbCell];

			// --- get nb of langage,  and id for first langage
			for (int row = 2; row < curSheet.nbRow; row++)
			{
				if (null == curSheet.getEntry(0, row))
				{
					break;
				}

				for (int cell = 0; cell < curSheet.nbCell; cell++)
				{
					str[cell] = curSheet.getEntry(cell, row);

					if (str[cell] == null)
					{
						break;
					}
				}

				writeTemplete(str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7], str[8]);
			}

			str = null;
		}

		closeFile();
	}
/*					
					if (str.compareToIgnoreCase("::ID::") == 0)
					{
						hash.put(new Integer(0), new Integer(cell));
						firstRow = row+1;
					}
					else if (	(str.startsWith("::")) 
							&& 	(str.endsWith("::")))
					{
						lang[nbLang] = str.toUpperCase().substring(2, str.length()-2);
						hash.put(new Integer(nbLang+1), new Integer(cell));
						nbLang++;
					}
				}
				// stop at ::ID:: row
				if (hash.get(new Integer(0)) != null )
				{
					break;
				}
			}

			if (hash.get(new Integer(0)) == null )
			{
				LOG("    sheet : "+curSheet.name+" : no valid langage definition found (::ID::, etc...)");
				log.append("    sheet : "+curSheet.name+" : no valid langage definition found (::ID::, etc...)\r\n");
				continue;
			}

			// define a new sheet
			defineSheet(curSheet.name);

			final int maxNbOflocalisationString = curSheet.nbRow;//1024;
			String [] id = new String[maxNbOflocalisationString];
			int [][] localisationOffset = new int[nbLang][maxNbOflocalisationString];

			final int maxLocalisationTextSize = 262144;
			byte [][] localisation = new byte[nbLang][maxLocalisationTextSize];

			// --- parse the sheet, pack all string in byte array
			int nbString = 0;
			for (int row=firstRow; row<curSheet.nbRow; row++)
			{
				// get string id
				id[nbString] = curSheet.getEntry(getInt(hash, 0), row);
				if (id[nbString] == null)
					continue;

				// define a new string
				id[nbString] = curSheet.name + "_" + id[nbString].trim();
				id[nbString] = id[nbString].replace(' ', '_');
				id[nbString] = id[nbString].toUpperCase();
				defineString(id[nbString], nbString);

				// pack all langage
				for (int j=0; j<nbLang; j++)
				{
					String text = curSheet.getEntry(getInt(hash, j+1), row);
					if (text == null)
					{
						text = "";
						log.append("sheet:"+curSheet.name+" "+lang[j]+" -> "+id[nbString]+" is empty (to be translated?)\r\n");
						warning.append("        "+id[nbString]+" in "+lang[j]+" is empty\r\n");
					}

					byte[] b = text.getBytes(encoding);
					int len = b.length;

					System.arraycopy(b, 0, localisation[j], localisationOffset[j][nbString], len);
					localisationOffset[j][nbString+1] = localisationOffset[j][nbString] + len;
				}

				nbString++;
				if (nbString >= maxNbOflocalisationString)
					ERR("too many localisation string in this sheet");
			}

			log.append("    sheet : "+curSheet.name+" ("+nbString+" text, "+ nbLang+" langage)\r\n");

			// export all langage to file
			for (int j=0; j<nbLang; j++)
			{
				System.out.print(".");
				//String filename = (sheet[i].name + "."+lang[j]);
				String ffilename = (curSheet.name + "_"+lang[j]+".lang");
				ffilename = ffilename.toUpperCase();

				outDir = getFilePath(outDir);
				ffilename = outDir+ffilename;

				FileOutputStream outt = new FileOutputStream(ffilename);

				// write nb of string
				write32(outt, nbString);

				// write offset to each string
				for (int k=0; k<nbString; k++)
				{
					write32(outt, localisationOffset[j][k+1]);
				}

				// write string
				outt.write(localisation[j], 0, localisationOffset[j][nbString]);

				//LOG("        lang "+j+" : "+lang[j]+" ("+(4+4*nbString+localisationOffset[j][nbString])+" byte)");
				log.append("        lang "+j+" : "+lang[j]+" ("+(4+4*nbString+localisationOffset[j][nbString])+" byte)\r\n");

				outt.close();
			}
		}
 */ 

//		System.out.print("\n");

//		// save log file
//		FileWriter out = new FileWriter( logName );
//		out.write(log.toString());
//		out.close();
		
//		// display warning
//		if (warning.length() > 0) 
//		{
//			System.out.println("    there were some warning:");
//			System.out.println(warning.toString());

//	}

	String outDir = ".\\";
	String headerDir = ".\\";
	String encoding = "UTF-8";
	
	void exec(String[] args) throws Exception
	{
		String OOFilename = null;
		
		// analyse argument
		for (int i=0; i<args.length; i++) 
		{
			if ((args[i].compareToIgnoreCase("-d") == 0) && (i+1<args.length)) {
				outDir = args[i+1];
				i++;
		
			} else if ((args[i].compareToIgnoreCase("-h") == 0) && (i+1<args.length)) {
				headerDir = args[i+1];
				i++;
		
			} else if ((args[i].compareToIgnoreCase("-e") == 0) && (i+1<args.length)) {
				encoding = args[i+1];
				i++;
				
			} else if ( args[i].toLowerCase().endsWith(".ods") ) {
				OOFilename = new String(args[i]);
				//LOG("process "+xmlFilename);
			}
		}
		
		if (OOFilename != null) 
		{
			parse(OOFilename);
		} else {
			ERR("no data file to parse");
		}
	}

		
	static public void main(String[] args)
	{
	    try {
	        ExportText m = new ExportText();
	        m.exec(args);
	    } catch(Exception e)
	    {
			LOG("ERROR:"+e);
		}
	}
	
}