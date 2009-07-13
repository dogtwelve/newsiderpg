

////////////////////////////////////////////////////////////////////////////////
// this script 
//   - increase the version number each time it is called
//   - add the line each line "MIDlet-Version: versionNumber" to the manifest file
//   - add the line each line "MIDlet-Version: versionNumber" to the jad file
//   - return the version number in the error level of dos command line
//
// syntax: 
//   java -jar BeanShell.jar increaseVersionNumber.Jscript directory manifestFile jadFile
// 		directory    : directory where the version nulber file is to be stored
//      manifestFile : path+name of the manifest file
//      jadFile      : path+name of the jad file
////////////////////////////////////////////////////////////////////////////////

import java.util.*;
import java.io.*;
import java.lang.*;
import java.io.FileWriter;

class increaseVersionNumber
{

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
    	System.err.println(a);
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




















int version = -1;
String versionString = null;
String filePattern="_version.";

// append MIDlet-Version line to a file
void proceed(String filename) throws Exception
{
	try {
		FileWriter file = new FileWriter(filename, true);
		String str = "MIDlet-Version: "+versionString+"\r\n";
		file.write(str);
		file.close();
	} catch (Exception e) {
		ERR("cannot open/modify file:"+filename);
		System.exit(-1);
	}
}

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

// create and set a version number file in path
boolean createFile(String path, int v) throws Exception
{
	int K = v / 1000;
	int D = (v - K*1000) / 100;
	int C = (v - D*100 - K*1000) / 10;
	int U = v - C*10 - D*100 - K*1000;
	
	version = v;
	versionString = K+"."+D+"."+C;
	//LOG(versionString);

	String filename = path+filePattern+versionString+"."+U;;
	
	File newFile = new File(filename);
	if (! newFile.createNewFile() ) {
		ERR("could not create file:"+filename);
		return false;
	}
	return true;
}

// get version nulber from version file in path
void getVersion(String path) throws Exception
{
	int i;
	path = getFilePath(path);

	File dir = new File(path);
	
	if (! dir.isDirectory() ) {
		ERR(path + " is not a directory");
		System.exit(-1);
	}

	String[] filelist;
	filelist = dir.list();
	
	String filename = null;
	
	if (filelist != null) {
		// search for a file
		for (i=0; i<filelist.length; i++) {
			if (filelist[i].indexOf(filePattern) >= 0) {
				filename = filelist[i];
				break;
			}
		}
	}
	
	// create a new file
	if (filename == null) {
		if (! createFile(path, 1) )
			System.exit(-1);
			
	// get version from file		
	} else {
		int ind = filename.indexOf(filePattern);
		ind += filePattern.length();
		String ver = filename.substring(ind, filename.length());
		ver = ver.replaceAll("\\.", "");
		//LOG("ver:"+ver);

		Integer in = new Integer(ver);
		if (! createFile( path, in.intValue() + 1 ) )
			System.exit(-1);
			
		File old = new File(path+filename);
		if (! old.delete() ) {
			ERR("could not remove file : "+path+filename);
		}
	}
}

	void exec(String[] args) throws Exception
	{
		try{
			if (args.length == 3) {
				getVersion(args[0]);
				if ((version != -1) && (versionString != null)) {
					proceed(args[1]);
					proceed(args[2]);
				}
			} else {
				ERR(args[0]+" invalid argument");
				System.exit(-1);
			}
			System.exit(version / 10);
		} catch (Exception e)
		{
			LOG("ERROR::"+e);
		}
	}

	static public void main(String[] args)
	{
	    try {
	        increaseVersionNumber m = new increaseVersionNumber();
	        m.exec(args);
	    } catch(Exception e)
	    { }
	}
	
}
