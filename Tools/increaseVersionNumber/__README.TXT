
increaseVersionNumber : increase the version number of a build by one
	append this version number to manifest and jadfile

	add the "MIDlet-Version: " filed in manifest and jad file
	
usage:
	java increaseVersionNumber <projectDirectory> <manifestfile> <jadFile>
	
	<projectDirectory> : directory of the project 
					(will store version number as a _version.X.X.X.X file)
	<manifestfile>	: path to the manifest file
	<jadFile> : path to the jadFile
