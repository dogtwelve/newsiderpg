
////////////////////////////////////////////////////////////////////////////////
// this script pack all data inside an excel xml file
// and generate java or C output file
//
// java -jar Beanshell.jar packFile.JScript <-java> <-release> <file.xml>
//     -java          output for java (if not present, output for C)
//     -release       generate short output name
//     file.xml       the excel xml file with the data definition
//
////////////////////////////////////////////////////////////////////////////////

import java.util.*;
import java.io.*;
import java.lang.*;

class packFile
{

	String dummy = "dummy";
	String packDefinition = "##";

    // --- verbose
	boolean verbose = false;
	boolean bigEndian = false;

            
    // --- LOG
    void LOG(String a)
    {
        System.out.println(a);
    }
            
    // --- ERR
    void ERR(String a)
    {
    	System.err.println("ERR::"+a);
    }
			
    // --- ASSERT
	void ASSERT(boolean cond, String a) throws Exception
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



	//source(scriptPath+"\\ExcelXmlParser.JScript");
	String outDir = ".\\";
	String inDir = ".\\";
	String headerDir = ".\\";


	String [][] mime = {
		{"unknown"},
		{"audio/x-wav",			"wav"},
		{"audio/midi",			"mid"},
		{"audio/mpeg",			"mp2","mp3","mp3pro","aac","aacPlus"},
		{"ott",					"ott"},
		{"audio/amr", 			"amr"},
		{"application/x-smaf", 	"mmf"},
		{"audio/basic", 		"au"},
		{"audio/x-vorbis", 		"ogg"},
		{"audio/3gpp", 			"3gp"},
		{"audio/amr-wb", 		"amr-wb"},
		{"audio/amr-wb+", 		"amr-wb+"},
		{"audio/x-gsm", 		"gsm-fr"},
		{"audio/x-gsmefr", 		"gsm_efr"},
		{"audio/qcelp", 		"qcelp"},
		{"audio/spmidi", 		"spmidi"},
		{"audio/x-realaudio", 	"real"},
		{"audio/x-aiff", 		"aiff"},
		{"audio/x-ms-wma", 		"wma"}
	
	};

	static FileWriter fd_define;
	static FileWriter fd_java;
	static boolean release = false;
	
	static FileWriter fd_defineC;
	//static FileWriter fd_defineJava;

	// get filepath given complete filename
	String getFilePath(String filename) throws Exception
	{
		int i;
		if ( (i = filename.lastIndexOf('\\')) != -1) {
			return filename.substring(0, i) + "\\";
	
		} else if ( (i = filename.lastIndexOf('/')) != -1) {
			filename = filename.substring(0, i) + "/";
			filename = filename.replaceAll("\\", "/");
			return filename;
		} else {
			return ".\\";
		}
	}
	
	String getPath(String path) throws Exception
	{
		File dir = new File(path);
		return dir.getAbsolutePath()+"\\";
	}

	void createDirectoryIfNotExist(String path) throws Exception
	{
		File dir = new File(path);
		if (dir.exists()) {
			if (! dir.isDirectory()){
				ERR(path+" already exist and is not a directory");
				throw new Exception(path+" already exist and is not a directory");
			}
		} else {
			dir.mkdir();
		}
	}



	void openFile() throws Exception
	{
		//headerDir = getFilePath(headerDir);
		//createDirectoryIfNotExist(headerDir+"C");
		//createDirectoryIfNotExist(headerDir+"java");
	
		fd_defineC = new FileWriter(headerDir+"Data.h");
		//fd_defineJava = new FileWriter(headerDir+"java\\DataGenerated.h");
		fd_defineC.write("#ifndef _DATA_H_\n");
		fd_defineC.write("#define _DATA_H_\n");
	
		fd_java = new FileWriter(headerDir+"Data.java");
	
		
		fd_java.write("interface Data\n");
		fd_java.write("{\n");
	
		//fd_defineJava.write("// this file is was created by the data exporter\n");
		//fd_defineJava.write("// use it in your java code if you intend to use the preprocessor in java\n");
	
	
	//	fd_define = new FileWriter("Define.h");
	//	fd_java = null;
	//	if (java) {
	//		fd_java = new FileWriter("Define.java");
	//		fd_java.write("class Define \n");
	//		fd_java.write("{\n");
	//	}
	
	}
	
	void closeFile() throws Exception
	{
		fd_defineC.write("\n#endif//_DATA_H_\n");
		fd_defineC.close();
		//fd_defineJava.close();
		fd_java.write("}\n");
		fd_java.close();
	}
	
	void defineInt(String pack, String name, int value) throws Exception
	{
		fd_defineC.write("#define "+pack+"_"+name+" \t\t\t "+value+" \n");
		//fd_defineJava.write("#define "+pack+"_"+name+" \t\t\t (DataGenerated."+pack+"_"+name+")\n");
		fd_java.write("\tfinal static int "+pack+"_"+name+" \t\t\t= "+value+";\n");
	}

	void definePack(String packName, String packFileName) throws Exception
	{
		fd_defineC.write("\n");
		fd_defineC.write("//------------------------------------------------------------------------------\n");
		fd_defineC.write("#define PACK_"+packName+" \t\t\t\"/"+packFileName+"\"\n");
		fd_defineC.write("\n");
	
		//fd_defineJava.write("\n");
		//fd_defineJava.write("//------------------------------------------------------------------------------\n");
		//fd_defineJava.write("#define PACK_"+packName+" \t\t\t DataGenerated.PACK_"+packName+"\n");
		//fd_defineJava.write("\n");
	
		fd_java.write("\n");
		fd_java.write("\t//--------------------------------------------------------------------------\n");
		fd_java.write("\tfinal static String  PACK_"+packName+" \t\t\t= \"/"+packFileName+"\";\n");
		fd_java.write("\n");
	}

	
	void parseXML(String ffname) throws Exception
	{
		int i, j, row, cell;
		FileInputStream fd_dataIn;
		FileOutputStream fd_dataOut;
		String packFileName;
		String packName;
		boolean exporting = false;
	
		StringBuffer log = new StringBuffer("");
		String logName = ffname+".log";
	
		int [] fat = new int[255];
		final int BUFFER_SIZE = 2048*1024;	// 2Mo
		byte [] data = new byte[BUFFER_SIZE];
	
		//File file = new File(filename);
		//filename = file.getAbsolutePath();
		//filename = filename.replace('\\', '/');
		//filename = filename.replaceAll("#", "\\\\#");
		//LOG("-->"+filename);
		//
	
		ExcelXmlParser parser = new ExcelXmlParser();
		WorkSheet[] sheet;
		sheet = parser.parse(ffname);
	
		openFile();
	//	fd_define = new FileWriter("Define.h");
	//	fd_java = null;
	//	if (java) {
	//		fd_java = new FileWriter("Define.java");
	//		fd_java.write("class Define \n");
	//		fd_java.write("{\n");
	//	}
	//System.out.print("\n");
		for (i=0; i<sheet.length; i++) {
	
	//		System.out.print("    .");
	
			int curOffset = 0;
	
			// set data export filename
			packName = sheet[i].name.toUpperCase();
	
			if (release) {
				packFileName = ""+i;
			} else {
				packFileName = packName + ".DAT";
	
			}
	
			// new pack
			definePack(packName, packFileName);
	
			log.append("\r\nnew pack : \\"+packFileName+"\t("+packName+")\r\n");
	
			String filename = null;
			String id = null;
			int curId = 0;
			int cell_id = -1;
			int cell_data = -1;
	
			for (row=0; row<sheet[i].nbRow; row++) {
	//			System.out.print(".");
				filename = null;
				id = null;
				for (cell=0; cell<sheet[i].nbCell; cell++) {
	
					if (sheet[i].table[cell][row] == null)
						continue;
	
					if (sheet[i].table[cell][row].compareToIgnoreCase("::ID::") == 0) {
						cell_id = cell;
						//LOG("cell_id:"+cell_id);
					} else if (sheet[i].table[cell][row].compareToIgnoreCase("::DATA::") == 0) {
						cell_data = cell;
						//LOG("cell_data:"+cell_data);
	
					} else {
						if (cell == cell_id) {
							id = sheet[i].table[cell][row].toUpperCase();
							//LOG("\tid:"+id);
						} else if (cell == cell_data) {
							filename = sheet[i].table[cell][row];
							//LOG("\tfi:"+filename);
						}
					}
				}
	
				if (id != null) {
					log.append("    data:"+curId+" -> "+packName.toUpperCase()+"_"+id.toUpperCase()+"\r\n");
	
					if (filename == null)
					{
						log.append("        considered as a dummy data\r\n");
						defineInt(packName, id, -1);
	
					}
					else
					{
	
						// add data to data file
						fat[curId] = curOffset;
	
						/*FileInputStream */fd_dataIn = null;
						filename = filename;
	
						try {
							fd_dataIn = new FileInputStream(outDir + filename);
						} catch(Exception e1) {
							ERR("file not found1:"+filename);
						}


						if (fd_dataIn == null) 
						{
							ERR("        considered as a dummy data\r\n");
							log.append("        considered as a dummy data\r\n");
							defineInt(packName, id, -1);
						}
						else
						{
							defineInt(packName, id, curId);
							// check special file format
							int mimeType = 0;
							for (int k=0; k<mime.length; k++) {
								for (int kk=0; kk<mime[k].length; kk++) {
									if (filename.toLowerCase().endsWith( mime[k][kk] )) {
										mimeType = k;
									}
								}
							}
							data[curOffset] = (byte) mimeType;
							curOffset++;
							log.append("        file         : "+filename+"\r\n");
							log.append("        MIME type    : "+mime[mimeType][0]+" ("+mimeType+")\r\n");
	
							int size = fd_dataIn.available();
							if (size+curOffset >= BUFFER_SIZE)
							{
								ERR("buffer to store data is too small");
								return;
							}
							fd_dataIn.read(data, curOffset, size);
							curOffset += size;
	//						while (fd_dataIn.available() > 0) {
	//							data[curOffset] = (byte) fd_dataIn.read();
	//							curOffset++;
	//						}
	//						fd_dataIn.close();
	//						File fi = new File(outDir + filename);
	//						fi.delete();
						}
						log.append("        size         : "+(curOffset - fat[curId])+" byte\r\n");
						log.append("        start@offset : "+fat[curId]+"\r\n");
						log.append("        end@offset   : "+curOffset+"\r\n");
	
						curId++;
					}
				}
	
			}
	//System.out.print("\n");
	
			// set end of data
			defineInt(packName, "MAX", curId);
	
			// save data file
			fd_dataOut = null;
			try {
				packFileName = outDir + packFileName;
				fd_dataOut = new FileOutputStream(packFileName.toUpperCase());
			} catch(Exception e2) {
				ERR("cannot create output file:"+packFileName);
			}
	
			if (fd_dataOut != null) {
	//LOG("\t\t nbdata:"+curId);
				// write nb of data
				write32(fd_dataOut, curId);
	
				// write fat table
				for (j=0; j<curId-1; j++){
					write32(fd_dataOut, fat[j+1]);
	//LOG("write "+j+" "+fat[j+1]);
				}
				write32(fd_dataOut, curOffset);
	//LOG("write "+(curId-1)+" "+curOffset);
	
				// write data
				fd_dataOut.write(data, 0, curOffset);
				fd_dataOut.close();
			}
	
		}
	
		closeFile();
	//	System.out.print("\n");
		// save file
		FileWriter out = new FileWriter( logName );
		out.write(log.toString());
		out.close();
	
	}


	void parse(String ffname) throws Exception
	{
		int curId = 0;
		int pakCnt = 0;
		String packName = null;
		String packFileName = null;
		int curOffset = 0;
		
		int i, j, row, cell;
//		FileInputStream fd_dataIn;
//		FileOutputStream fd_dataOut;
		boolean exporting = false;
	
		StringBuffer log = new StringBuffer("");
		String logName = ffname+".log";
	
		int [] fat = new int[255];
		final int BUFFER_SIZE = 2048*1024;	// 2Mo
		byte [] data = new byte[BUFFER_SIZE];
	
	
//		ExcelXmlParser parser = new ExcelXmlParser();
//		WorkSheet[] sheet;
//		sheet = parser.parse(ffname);
	
		LineNumberReader in = new LineNumberReader( new FileReader(ffname) );
		openFile();
		String s = null;

		while ((s = in.readLine()) != null)
		{
			// remove comment
			i = s.indexOf("//");
			if (i >= 0)
			{
				s = s.substring(0, i);
			}

			// trim
			if (s.length() > 0)
				s.trim();
			if (s.length() <= 0)
				continue;
			
			// pack name
			i = s.indexOf(packDefinition);
			if (i >= 0)
			{
				
				if (packName != null)
				{
					// set end of data
					defineInt(packName, "MAX", curId);
					
					// save data file
					FileOutputStream fd_dataOut = null;
					try 
					{
						packFileName = outDir + packFileName;
						fd_dataOut = new FileOutputStream(packFileName.toUpperCase());
					}
					catch(Exception e2) 
					{
						ERR("cannot create output file:"+packFileName);
					}
					
					if (fd_dataOut != null) 
					{
						// write nb of data
						write32(fd_dataOut, curId);
	
						// write fat table
						for (j=0; j<curId-1; j++)
						{
							write32(fd_dataOut, fat[j+1]);
							//LOG("write "+j+" "+fat[j+1]);
						}
						write32(fd_dataOut, curOffset);
						//LOG("write "+(curId-1)+" "+curOffset);
	
						// write data
						fd_dataOut.write(data, 0, curOffset);
						fd_dataOut.close();
					}
					
					packName = null;
				}
				
				packName = s.substring(i+packDefinition.length(), s.length()).trim().toUpperCase();
				if (release) 
				{
					packFileName = ""+pakCnt;
					pakCnt++;
				}
				else 
				{
					packFileName = packName + ".DAT";
		
				}
				// new pack
				definePack(packName, packFileName);
				log.append("\r\nnew pack : \\"+packFileName+"\t("+packName+")\r\n");
				curId = 0;
				curOffset = 0;
				continue;
			}
			
			// data to put inside pack
			i = s.indexOf("\t");
			if (i > 0)
			{
				String filename = null;
				String id = null;
				
				id = s.substring(0, i).trim().toUpperCase();
				filename = s.substring(i, s.length()).trim();
				
				log.append("    data:"+curId+" -> "+packName.toUpperCase()+"_"+id+"\r\n");

				if (filename.compareTo(dummy) == 0)
				{
					log.append("        considered as a dummy data\r\n");
					defineInt(packName, id, -1);
				}
				else
				{

					// add data to data file
					fat[curId] = curOffset;
					
					FileInputStream fd_dataIn = null;
					try 
					{
						fd_dataIn = new FileInputStream(inDir + filename);
					}
					catch(Exception e1) 
					{
						ERR("file not found:"+inDir + filename);
					}
					
					if (fd_dataIn == null) 
					{
						ERR("        considered as a dummy data");
						log.append("        considered as a dummy data\r\n");
						defineInt(packName, id, -1);
					}
					else
					{
						defineInt(packName, id, curId);
						
						// check special file format
						int mimeType = 0;
						for (int k=0; k<mime.length; k++) {
							for (int kk=0; kk<mime[k].length; kk++) {
								if (filename.toLowerCase().endsWith( mime[k][kk] )) {
									mimeType = k;
								}
							}
						}
						data[curOffset] = (byte) mimeType;
						curOffset++;
						log.append("        file         : "+filename+"\r\n");
						log.append("        MIME type    : "+mime[mimeType][0]+" ("+mimeType+")\r\n");

						int size = fd_dataIn.available();
						if (size+curOffset >= BUFFER_SIZE)
						{
							ERR("buffer to store data is too small");
							return;
						}
						fd_dataIn.read(data, curOffset, size);
						curOffset += size;
					}
					log.append("        size         : "+(curOffset - fat[curId])+" byte\r\n");
					log.append("        start@offset : "+fat[curId]+"\r\n");
					log.append("        end@offset   : "+curOffset+"\r\n");

					curId++;
				}
				
				
			}


		}
		// save last pack
		if (packName != null)
		{
			// set end of data
			defineInt(packName, "MAX", curId);

			// save data file
			FileOutputStream fd_dataOut = null;
			try 
			{
				packFileName = outDir + packFileName;
				fd_dataOut = new FileOutputStream(packFileName.toUpperCase());
			}
			catch(Exception e2) 
			{
				ERR("cannot create output file:"+packFileName);
			}

			if (fd_dataOut != null) 
			{
				// write nb of data
				write32(fd_dataOut, curId);

				// write fat table
				for (j=0; j<curId-1; j++)
				{
					write32(fd_dataOut, fat[j+1]);
					//LOG("write "+j+" "+fat[j+1]);
				}
				write32(fd_dataOut, curOffset);
				//LOG("write "+(curId-1)+" "+curOffset);

				// write data
				fd_dataOut.write(data, 0, curOffset);
				fd_dataOut.close();
			}

			packName = null;
		}
		in.close();

		closeFile();
		// save file
		FileWriter out = new FileWriter( logName );
		out.write(log.toString());
		out.close();
	
	}

	void exec(String[] args)
	{
		try
		{
			String iniFilename = null;
			//release = false;
			release = true;
			for (int i=0; i<args.length; i++) 
			{
				
				if ((args[i].compareToIgnoreCase("-i") == 0) && (i+1<args.length)) {
					inDir = args[i+1];
					inDir = getPath(inDir);
					i++;
			
				} 
				else if ((args[i].compareToIgnoreCase("-d") == 0) && (i+1<args.length)) {
					outDir = args[i+1];
					outDir = getPath(outDir);
					i++;
			
				} 
				else if ((args[i].compareToIgnoreCase("-h") == 0) && (i+1<args.length)) 
				{
					headerDir = args[i+1];
					headerDir = getPath(headerDir);
					i++;
			
				}
				else if (args[i].compareToIgnoreCase("-release") == 0) 
				{
					release = true;
					//LOG("release");
				}
				else if ( args[i].toLowerCase().endsWith(".ini") ) 
				{
					iniFilename = new String(args[i]);
					//LOG("process "+iniFilename);
				}
			}

			if (iniFilename != null) 
			{
				parse(iniFilename);
			}
			else 
			{
				ERR("no data file to parse");
			}
		}
		catch (Exception e)
		{
			LOG("ERROR::"+e);
		}
	}

	static public void main(String[] args)
	{
	    try 
		{
	        packFile m = new packFile();
	        m.exec(args);
	    }
		catch(Exception e)
	    { 
		}
	}
}

//packFile.main(args);

