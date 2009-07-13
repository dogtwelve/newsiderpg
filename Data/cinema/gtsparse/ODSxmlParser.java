

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

	final int MAX_CELL_SIZE = 1024;
	final int MAX_ROW_SIZE = 2048;

	/// table in this sheet
	String [][] table;

	WorkSheet()
	{
		name 	= null;
		table = new String[MAX_CELL_SIZE][MAX_ROW_SIZE];
	}

	void setName(String _name)
	{
		name = new String(_name);
	}

	// adjust sheet to real size
	void packTable()
	{
		String[][] table2 = new String[nbCell][nbRow];
		for (int i=0; i<nbCell; i++)
			for (int j=0; j<nbRow; j++)
				table2[i][j] = table[i][j];
		table = table2;
		System.gc();

		// for (int j=0; j<nbRow; j++)
		// {
			// for (int i=0; i<nbCell; i++)
			// {
				// System.out.print(" ** "+table[i][j]);
			// }
			// System.out.print("\n");
		// }

		// inverted order
		// for (int j=0; j<nbCell; j++)
		// {
			// for (int i=0; i<nbRow; i++)
			// {
				// System.out.print(" ** "+table[j][i]);
			// }
			// System.out.print("\n");
		// }
	}

	String getEntry(int cell, int row)
	{
		if ((table != null) && (cell < nbCell) && (row < nbRow))
		{
			//System.out.println(">>> cell: "+ cell + "   row: " + row + "   table[cell][row]: " + table[cell][row]);
			return table[cell][row];
		}
		return null;
	}

	int curRow = 0;
	int curCell = 0;

	void newRow()
	{
		curRow++;
		curCell = 0;
		nbRow = curRow + 1;
	}

	void setTable(String value, int nbRepeat, int spanAccrossCell, int spanAcrossRow)
	{
		if (table == null)
			return;

		for (int i=0; i<spanAccrossCell*nbRepeat; i++)
		{
			while (table[curCell][curRow] != null)
				curCell++;
			for (int j=0; j<spanAcrossRow; j++)
			{
				table[curCell][curRow+j] = value;
				//System.out.println(">>> curCell: "+ curCell + "   (curRow+j): " + (curRow+j) + "   value: " + value);
			}
			curCell++;
		}

		if (curCell > nbCell)
			nbCell = curCell;
	}
};


//<?xml version="1.0" encoding="UTF-8"?>
//<office:document-content xmlns:office="urn:oasis:names:tc:opendocument:xmlns:office:1.0" xmlns:style="urn:oasis:names:tc:opendocument:xmlns:style:1.0" xmlns:text="urn:oasis:names:tc:opendocument:xmlns:text:1.0" xmlns:table="urn:oasis:names:tc:opendocument:xmlns:table:1.0" xmlns:draw="urn:oasis:names:tc:opendocument:xmlns:drawing:1.0" xmlns:fo="urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:meta="urn:oasis:names:tc:opendocument:xmlns:meta:1.0" xmlns:number="urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0" xmlns:svg="urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0" xmlns:chart="urn:oasis:names:tc:opendocument:xmlns:chart:1.0" xmlns:dr3d="urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0" xmlns:math="http://www.w3.org/1998/Math/MathML" xmlns:form="urn:oasis:names:tc:opendocument:xmlns:form:1.0" xmlns:script="urn:oasis:names:tc:opendocument:xmlns:script:1.0" xmlns:ooo="http://openoffice.org/2004/office" xmlns:ooow="http://openoffice.org/2004/writer" xmlns:oooc="http://openoffice.org/2004/calc" xmlns:dom="http://www.w3.org/2001/xml-events" xmlns:xforms="http://www.w3.org/2002/xforms" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" office:version="1.0">
//	<office:scripts/>
//	<office:font-face-decls>
//		<style:font-face style:name="Arial1" svg:font-family="Arial1"/>
//	</office:font-face-decls>
//	<office:automatic-styles>
//		<style:style style:name="co1" style:family="table-column">
//			<style:table-column-properties fo:break-before="auto" style:column-width="5.53cm"/>
//		</style:style>
//	</office:automatic-styles>
//
//	<office:body>
//		<office:spreadsheet>
//			<table:table table:name="init" table:style-name="ta1">
//				<office:forms form:automatic-focus="false" form:apply-design-mode="false"/>
//				<table:table-column table:style-name="co1" table:default-cell-style-name="ce2"/>
//
//				<table:table-row table:style-name="ro1">
//					<table:table-cell table:style-name="ce1" office:value-type="string">
//						<text:p>::Id::</text:p>
//					</table:table-cell>
//					<table:table-cell table:style-name="ce1" office:value-type="string">
//						<text:p>::pt::</text:p>
//					</table:table-cell>
//				</table:table-row>
//
//				<table:table-row table:style-name="ro1">
//					<table:table-cell table:style-name="Default" table:number-columns-repeated="8"/>
//				</table:table-row>
//
//				<table:table-row table:style-name="ro1">
//					<table:table-cell office:value-type="string">
//						<text:p>SELECT_LANGUAGE</text:p>
//					</table:table-cell>
//				</table:table-row>
//					<table:table-cell table:number-columns-repeated="2" office:value-type="string">
//						<text:p>VOLTAR</text:p>
//					</table:table-cell>
//			</table:table>
//
//			<table:table table:name="menu" table:style-name="ta1">
//				<office:forms form:automatic-focus="false" form:apply-design-mode="false"/>
//				<table:table-column table:style-name="co9" table:default-cell-style-name="Default"/>
//				<table:table-row table:style-name="ro1">
//					<table:table-cell table:style-name="ce1" office:value-type="string">
//						<text:p>::Id::</text:p>
//					</table:table-cell>
//				</table:table-row>
//			</table:table>
//		</office:spreadsheet>
//	</office:body>
//</office:document-content>

class ODSXmlParser extends DefaultHandler
{
	boolean verbose = false;
	static Vector ODSXmlFile;
	static int currentRow;
	static int currentCell;
	static int dataType;	//0:String 1:Number 2:Other
	static String charbuf = null;

	static WorkSheet curWorksheet = null;
	static int table_nb_columns_repeat = 1;
	static int table_nb_column_spanned = 1;
	static int table_nb_rows_spanned = 1;
	static int nbRow = 0;
	static int nbCol = 0;
	static boolean office_annotation_skipCapture =false;
	static boolean covered_table_cell_skipCapture = false;
	int curCol = -1;



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

	WorkSheet[] parse(InputStream is)
	{
		int i;

		ODSXmlFile = new Vector();
		ODSXmlFile.clear();

		if (verbose)
			LOG("ODSXmlParser parsing");

		// Use an instance of ourselves as the SAX event handler
		DefaultHandler handler = new ODSXmlParser();

		// Use the default (non-validating) parser
		SAXParserFactory factory = SAXParserFactory.newInstance();

		// parse
		try
		{
			SAXParser saxParser = factory.newSAXParser();
			saxParser.parse(is, handler);
		}
		catch (org.xml.sax.SAXParseException pe)
		{
			ERR("ODSXmlParser::SAXParseException:: " + pe);
			LOG("col,line:"+pe.getColumnNumber()+","+pe.getLineNumber() +" "+pe.getPublicId()+" "+pe.getSystemId());
		}
		catch (Exception e)
		{
			ERR("ODSXmlParser::parser error:: " + e);
		}

		// prepare data for output
		WorkSheet[] out;
		out = new WorkSheet[ ODSXmlFile.size() ];
		for (i=0; i<ODSXmlFile.size(); i++)
		{
			out[i] = (WorkSheet) ODSXmlFile.elementAt(i);
		}
		return out;
	}

	//===========================================================
    // SAX DocumentHandler methods
    //===========================================================
    public void characters(char []buf, int offset, int len) throws SAXException
    {
    	if (	(charbuf != null)
			&& 	(office_annotation_skipCapture == false)
			&&	(covered_table_cell_skipCapture == false)
			)
		{
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
		if (qname.compareToIgnoreCase("table:table") == 0)
		{
			if (verbose)
				LOG("new Worksheet:");

			curWorksheet = new WorkSheet();
			curWorksheet.setName( attrs.getValue("table:name") );
			nbCol = 0;
			currentRow = 0;

			if (verbose)
				LOG("    name:"+curWorksheet.name);
		}
		else if (qname.compareToIgnoreCase("table:table-source") == 0)
		{
			if (verbose)
				LOG("skipping external source:"+curWorksheet.name);
			curWorksheet = null;
		}
		else if (qname.compareToIgnoreCase("table:table-column") == 0)
		{
			// String strNbRepeat = attrs.getValue("table:number-columns-repeated"); // stoopid field
			// if(strNbRepeat != null)
				// nbCol += Integer.decode(strNbRepeat).intValue();
			// else
				// nbCol ++;
			// if (verbose)
				// LOG("\t new col :"+nbCol);
		}
		else if (qname.compareToIgnoreCase("table:table-row") == 0)
		{
			if (curWorksheet == null)
				return;
			curWorksheet.newRow();
			if (verbose)
				LOG("\t\t new row");
		}
		else if (qname.compareToIgnoreCase("table:table-cell") == 0)
		{
			office_annotation_skipCapture = false;
			covered_table_cell_skipCapture = false;
			String str = attrs.getValue("table:number-columns-repeated"); // stoopid field
			if (str == null)
				table_nb_columns_repeat = 1;
			else
				table_nb_columns_repeat = Integer.decode(str).intValue();

			str = attrs.getValue("table:number-columns-spanned"); // stoopid field
			if (str == null)
				table_nb_column_spanned = 1;
			else
				table_nb_column_spanned = Integer.decode(str).intValue();

			str = attrs.getValue("table:number-rows-spanned"); // stoopid field
			if (str == null)
				table_nb_rows_spanned = 1;
			else
				table_nb_rows_spanned = Integer.decode(str).intValue();

			if (verbose)
				LOG("\t\t\t new cell "+table_nb_column_spanned+" "+table_nb_rows_spanned+" "+table_nb_columns_repeat);
		}
		else if (qname.compareToIgnoreCase("table:covered-table-cell") == 0)
		{
			covered_table_cell_skipCapture = true;
		}
		else if (qname.compareToIgnoreCase("office:annotation") == 0)
		{
			office_annotation_skipCapture = true;
		}
		else if ((qname.compareToIgnoreCase("text:p") == 0) && (office_annotation_skipCapture == false) && (covered_table_cell_skipCapture == false))
		{
			if (charbuf != null)
			{
				charbuf += "\n";
			}
			else
			{
				charbuf = new String("");
			}
			if (verbose)
				LOG("\t\t\t\t new data");
		}
		else if ((qname.compareToIgnoreCase("text:s") == 0) && (office_annotation_skipCapture == false) && (covered_table_cell_skipCapture == false))
		{
			if (charbuf != null)
			{
				String strNbRepeat = attrs.getValue("text:c");
				int nbSpaceRepeat = 0;
				if(strNbRepeat == null)
					nbSpaceRepeat = 1;
				else
					nbSpaceRepeat = Integer.decode(strNbRepeat).intValue();
				for (int i=0; i<nbSpaceRepeat; i++)
				{
					charbuf += " ";
				}
			}
		}
		else if ((qname.compareToIgnoreCase("text:line-break") == 0) && (office_annotation_skipCapture == false) && (covered_table_cell_skipCapture == false))
		{
			if (charbuf != null)
			{
				charbuf += "\n";
			}
		}
		else if ((qname.compareToIgnoreCase("text:tab-stop") == 0) && (office_annotation_skipCapture == false) && (covered_table_cell_skipCapture == false))
		{
			if (charbuf != null)
			{
				charbuf += "\t";
			}
		}

 	}

    public void endElement(String namespaceURI, String sName, String qname) throws SAXException
    {
		if (qname.compareToIgnoreCase("table:table") == 0)
		{
			if (	(curWorksheet != null)
				&&	(curWorksheet.table != null)	// do not add sheet with no table
				)
			{
				curWorksheet.packTable();
				ODSXmlFile.add( curWorksheet );
			}
			curWorksheet = null;
		}
		else if (qname.compareToIgnoreCase("table:table-row") == 0)
		{
		}
		else if (qname.compareToIgnoreCase("table:table-cell") == 0)
		{
			if (curWorksheet  == null)
				return;

			if (verbose)
				LOG("\t\t\t\t    "+charbuf);
			curWorksheet.setTable(charbuf, table_nb_columns_repeat, table_nb_column_spanned, table_nb_rows_spanned);
			charbuf = null;
		}
		else if (qname.compareToIgnoreCase("table:covered-table-cell") == 0)
		{
			covered_table_cell_skipCapture = false;
		}
		else if (qname.compareToIgnoreCase("office:annotation") == 0)
		{
			office_annotation_skipCapture = false;
		}
		else if ((qname.compareToIgnoreCase("text:p") == 0) && (office_annotation_skipCapture == false)  && (covered_table_cell_skipCapture == false))
		{
		}
    }
};
