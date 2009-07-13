

////////////////////////////////////////////////////////////////////////////////
// this script create/add file to a data File
////////////////////////////////////////////////////////////////////////////////
import org.xml.sax.*;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;

import java.util.*;
import java.io.*;
import java.lang.reflect.Array;


/// represent a sheet in excel
class WorkSheet
{
	boolean verbose = false;
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
	/// name of the sheet
	String name;
	
	/// nb of row in this sheet
	int nbRow;
	
	/// nb of cell in this sheet
	int nbCell;

	/// table in this sheet
	String [][] table;

	WorkSheet()
	{
		name 	= null;
		nbRow	= 0;
		nbCell	= 0;
		table 	= null;
	}
	
	void setName(String _name)
	{
		name = new String(_name);
	}

	void setNbRow(int _row)
	{
		nbRow = _row;
	}

	void setNbRow(String _row)
	{
		nbRow = Integer.decode(_row).intValue();
	}


	void setNbCell(int _cell)
	{
		nbCell = _cell;
	}

	void setNbCell(String _cell)
	{
		nbCell = Integer.decode(_cell).intValue();
	}


	void createTable()
	{
		if ( (nbRow + nbCell) != 0)
			table = new String[nbCell][nbRow];
	}
	
	void setTable(int cell, int row, String value)
	{
		if (	(table != null)
			&&	(cell < nbCell)
			&&	(cell < nbRow)
			)
			table[cell][row] = new String(value);
	}
};




//<?mso-application progid="Excel.Sheet"?>
//<Workbook ...>
//	<DocumentProperties xmlns="urn:schemas-microsoft-com:office:office">
//		<Author>bramard</Author>
//		<LastAuthor>bramard</LastAuthor>
//		<Created>2005-09-22T09:19:10Z</Created>
//		<Company>UBISOFT</Company>
//		<Version>11.6408</Version>
//	</DocumentProperties>
//	<ExcelWorkbook xmlns="urn:schemas-microsoft-com:office:excel">
//		...
//	</ExcelWorkbook>
//	<Styles>
//		...
//	</Styles>
//	<Worksheet ss:Name="data1">
//		<Table ss:ExpandedColumnCount="4" ss:ExpandedRowCount="35" x:FullColumns="1" x:FullRows="1" ss:DefaultColumnWidth="60">
//			<Row ss:Index="row number">
//				<Cell ss:Index="cell number" ss:StyleID="style id">
//					<Data ss:Type="String">::-file::nb.dat</Data>
//				</Cell>
//				<Cell>
//					<Data ss:Type="Number">12</Data>
//				</Cell>
//			</Row>
//		</Table>
//	</Worksheet>
//	<Worksheet ss:Name="worksheet name">
//		...
//	</Worksheet>
//</Workbook>

class ExcelXmlParser extends DefaultHandler
{
	boolean verbose = false;
	static Vector ExcelXmlFile;
	static int currentRow;
	static int currentCell;
	static int dataType;	//0:String 1:Number 2:Other
	static String charbuf = null;
	static WorkSheet curWorksheet;
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
	WorkSheet[] parse(String filename)
	{
		int i;
		
		ExcelXmlFile = new Vector();
		ExcelXmlFile.clear();
	
		if (verbose)
			LOG("ExcelXmlParser parsing "+filename);

		// Use an instance of ourselves as the SAX event handler
		DefaultHandler handler = new ExcelXmlParser();

		// Use the default (non-validating) parser
		SAXParserFactory factory = SAXParserFactory.newInstance();

		// parse
		try {
			SAXParser saxParser = factory.newSAXParser();
			saxParser.parse( new File(filename), handler);
		} catch (org.xml.sax.SAXParseException pe) {
			ERR("ExcelXmlParser::SAXParseException:: " + pe);
			LOG("col,line:"+pe.getColumnNumber()+","+pe.getLineNumber() +" "+pe.getPublicId()+" "+pe.getSystemId());
			
		} catch (Exception e) {
			ERR("ExcelXmlParser::parser error:: " + e);
		}

		// prepare data for output		
		WorkSheet[] out;
		out = new WorkSheet[ ExcelXmlFile.size() ];
		for (i=0; i<ExcelXmlFile.size(); i++) {
			out[i] = (WorkSheet) ExcelXmlFile.elementAt(i); 
		}
		return out;
	}
	
	
	
  //===========================================================
    // SAX DocumentHandler methods
    //===========================================================

    public void characters(char []buf, int offset, int len) throws SAXException
    {
    	if (charbuf != null) {
			charbuf += new String(buf, offset, len);	
    	}
    }	
	
    public void startDocument() throws SAXException
    {
    	if (verbose)
    		LOG(">>> startDocument");
    }

    public void endDocument() throws SAXException
    {
    	if (verbose)
    		LOG(">>> endDocument");
    }	
    
	public void startElement(String namespaceURI, String lName, String qname, Attributes attrs) throws SAXException
    {
		charbuf = null;

		if (qname.compareToIgnoreCase("Worksheet") == 0) {
			
			curWorksheet = new WorkSheet();
			curWorksheet.setName( attrs.getValue("ss:Name") );
			
			if (verbose)
				LOG("new Worksheet name:"+curWorksheet.name);

		} else if (qname.compareToIgnoreCase("Table") == 0) {

//			curWorksheet.setNbRow( Integer.decode( attrs.getValue("ss:ExpandedRowCount") ).intValue() );
//			curWorksheet.setNbCell( Integer.decode(attrs.getValue("ss:ExpandedColumnCount") ).intValue() );
			curWorksheet.setNbRow( attrs.getValue("ss:ExpandedRowCount") );
			curWorksheet.setNbCell( attrs.getValue("ss:ExpandedColumnCount") );
			curWorksheet.createTable();
			currentRow = -1;

			if (verbose)
				LOG("\t new Table maxNbOfRow:"+curWorksheet.nbRow+" maxNbOfCell:"+curWorksheet.nbCell);

		} else if (qname.compareToIgnoreCase("Row") == 0) {
			currentCell = -1;
			if (attrs.getValue("ss:Index") != null) {
				currentRow = Integer.decode( attrs.getValue("ss:Index") ).intValue() - 1;
			} else {
				currentRow++;
			}
			
			if (verbose)
				LOG("\t\t new row currentRow:"+currentRow);

		} else if (qname.compareToIgnoreCase("Cell") == 0) {
			if (attrs.getValue("ss:Index") != null) {
				currentCell = Integer.decode( attrs.getValue("ss:Index") ).intValue() - 1;
			} else {
				currentCell++;
			}

			if (verbose)
				LOG("\t\t\t new cell currentCell:"+currentCell);
			
		} else if (qname.compareToIgnoreCase("Data") == 0) {
			charbuf = new String("");
			if ( attrs.getValue("ss:Type").compareToIgnoreCase("String") == 0) {
				dataType = 0;
			} else if ( attrs.getValue("ss:Type").compareToIgnoreCase("Number") == 0) {
				dataType = 1;
			} else {
				dataType = 2;
			}
			
			if (verbose)
				LOG("\t\t\t\t new data dataType:"+dataType);
		}
 	}    
 	
    public void endElement(String namespaceURI, String sName, String qname) throws SAXException
    {
		if (qname.compareToIgnoreCase("Worksheet") == 0) {
			if (	(curWorksheet != null)
				&&	(curWorksheet.table != null)	// do not add sheet with no table
				) {
				ExcelXmlFile.add( curWorksheet );
			}
			curWorksheet = null;

    	} else if (qname.compareToIgnoreCase("Data") == 0){
	 		if (charbuf != null) {
	 			switch(dataType) {
	 			case 0:// string
	 			case 1://number
	 			default://
	 				curWorksheet.setTable(currentCell, currentRow, charbuf);
					if (verbose)
						LOG("\t\t\t\t\t ->:"+curWorksheet.table[currentCell][currentRow]);
	 			break;
	 			}
			}
    		charbuf = null;
    	}
    }    
};
