#@author: QiBinYi  , 2006
#export anims.h  anims.java , from anims.sprite

import os, sys, struct, re, glob
usage = "usage: python %s <sprite file>" %         os.path.basename(sys.argv[0])

_NAME_ANIMS=[]
_NAME_FRAMES=[]
_NAME_MODULES=[]

targetFileName = "all_sprites"

#--------------------------------------------------------------------
def ReadModules(spriteLines):
	#print 'ReadModules'
	modules = []
	for line in spriteLines:
		#MD	0x1001	MD_IMAGE	0	27	0	27	27
		foundModule = re.match('\s*MD\s+(?P<ID>\w+)\s+(MD_IMAGE)\s+(\d+)\s+(\d+)\s+(\d+)\s+(?P<WIDTH>\d+)\s+(?P<HEIGHT>\d+)\s+.*', line)
		if (foundModule != None):
			#print '   ' + foundModule.group('ID') + ' ' + foundModule.group('WIDTH') + ' ' + foundModule.group('HEIGHT')
			modules.append((foundModule.group('ID'), int(foundModule.group('WIDTH')), int(foundModule.group('HEIGHT'))))
			
	return modules
	
#--------------------------------------------------------------------	
def ReadFModules(spriteLines):
	#print 'ReadFModules'
	frame = []
	frames = []
	for line in spriteLines:
		#FRAME "Tweezers" // Index = 1, FModules = 1
		foundFrame = re.match('\s*FRAME\s+(")(?P<DESC>\w+)(")\s+(//)\s+(Index)\s+(=)\s+(?P<INDEX>\d+)(,)\s+.*', line)
		if (foundFrame != None):
			if (frame):
				frames.append(frame)
				frame = []
		
		#Append frame with no description to avoid wrong index
		else:
			foundFrame = re.match('\s*FRAME\s+.*', line)
			if (foundFrame != None):
				if (frame):
					frames.append(frame)
					frame = []

		#FM	0x1001	0	0
		foundFModule = re.match('\s*FM\s+(?P<ID>\w+)\s+(?P<X>\d+)\s+(?P<Y>\d+)\s+.*', line)
		if (foundFModule != None):
			#print '      ' + foundFModule.group('ID') + ' ' + foundFModule.group('X') + ' ' + foundFModule.group('Y')
			frame.append((foundFModule.group('ID'), int(foundFModule.group('X')), int(foundFModule.group('Y'))))
		
		else:
			foundFModule = re.match('\s*FM\s+(?P<ID>\w+)\s+(?P<X>\-\d+)\s+(?P<Y>\d+)\s+.*', line)
			if (foundFModule != None):
				#print '      ' + foundFModule.group('ID') + ' ' + foundFModule.group('X') + ' ' + foundFModule.group('Y')
				frame.append((foundFModule.group('ID'), int(foundFModule.group('X')), int(foundFModule.group('Y'))))
			
			else:
				foundFModule = re.match('\s*FM\s+(?P<ID>\w+)\s+(?P<X>\d+)\s+(?P<Y>\-\d+)\s+.*', line)
				if (foundFModule != None):
					#print '      ' + foundFModule.group('ID') + ' ' + foundFModule.group('X') + ' ' + foundFModule.group('Y')
					frame.append((foundFModule.group('ID'), int(foundFModule.group('X')), int(foundFModule.group('Y'))))
				
				else:
					foundFModule = re.match('\s*FM\s+(?P<ID>\w+)\s+(?P<X>\-\d+)\s+(?P<Y>\-\d+)\s+.*', line)
					if (foundFModule != None):
						#print '      ' + foundFModule.group('ID') + ' ' + foundFModule.group('X') + ' ' + foundFModule.group('Y')
						frame.append((foundFModule.group('ID'), int(foundFModule.group('X')), int(foundFModule.group('Y'))))

	if (frame):
		frames.append(frame)

	#print len(frames)	
	return frames

#--------------------------------------------------------------------	
def BuildConstantsTable(modules, frame):
	#print 'BuildConstantsTable'
	minX = 99999
	minY = 99999
	maxX = -99999
	maxY = -99999
	
	for fmodule in frame:
		#fmodule[0] fmoduleIndex
		#fmodule[1] posX
		#fmodule[2] posY
                #print '==========='
		for module in modules:
			#module[0] moduleIndex
			#module[1] width
			#module[2] height
                        #print ' '
                        #print '*****'
                        #print fmodule[1]
                        #print fmodule[2]
                        #print module[1]
                        #print module[2]
			if fmodule[0] == module[0]:
				if( fmodule[1] < minX ):
					minX = fmodule[1]
					
				if( fmodule[2] < minY ):
					minY = fmodule[2]
					
				if( (fmodule[1] + module[1]) > maxX ):
					maxX = fmodule[1] + module[1]
					
				if( (fmodule[2] + module[2]) > maxY ):
					maxY = fmodule[2] + module[2]
				
	#print '         ',
	#print maxWidth,
	#print maxHeight
	return (int(maxX - minX), int(maxY - minY))

#--------------------------------------------------------------------
def processSprite(fileName, maxModuleSize):
	# First read the content of the file
	fp = open(fileName, "r")
	sprite = fp.readlines()
	fp.close()
	
	modules	= ReadModules(sprite)
	frames 	= ReadFModules(sprite)
	
	NAME_TYPE=0
	NAME_ANIM=1
	
	MODULE_WIDTH_ID		= 6
	MODULE_HEIGHT_ID	= 7
	MODULE_NAME			= 8

	cnt = 0

	for line in sprite[2:]:
		line = line.strip()
		line = re.split("\s+", line)
		
		if line[NAME_TYPE] == "ANIM":
			strID = NAME_ANIM

			while line[strID][-1] != '\"':
				strID = strID + 1
				line[NAME_ANIM] = line[NAME_ANIM] + '_' + line[strID]

			_NAME_ANIMS.append(str.upper(line[NAME_ANIM][1:-1]))
		elif line[NAME_TYPE] == "FRAME":
			try:
				strID = NAME_ANIM
				
				while line[strID][-1] != '\"':
					strID = strID + 1
					line[NAME_ANIM] = line[NAME_ANIM] + '_' + line[strID]
	
				line[NAME_ANIM] = line[NAME_ANIM][1:-1]
				firstChar = ord(line[NAME_ANIM][0])
	
				#test if the first char is a digit
				if firstChar == 95: #underscore
					line[NAME_ANIM] = "_u"
				elif firstChar >= 48 and firstChar <= 57:
					line[NAME_ANIM] = '_' + line[NAME_ANIM]
				elif not ((firstChar >= 65 and firstChar <= 90) or (firstChar >= 97 and firstChar <= 122)):
					line[NAME_ANIM] = '_s' + str(cnt)
					cnt = cnt + 1
	
				_NAME_FRAMES.append(str.upper(line[NAME_ANIM]))
			except:
				_NAME_FRAMES.append("")
		elif line[NAME_TYPE] == "MD":
			try:
				strID = MODULE_NAME

				while line[strID][-1] != '\"':
					strID = strID + 1
					line[MODULE_NAME] = line[MODULE_NAME] + '_' + line[strID]

				line[MODULE_NAME] = line[MODULE_NAME][1:-1]
				firstChar = ord(line[MODULE_NAME][0])

				#test if the first char is a digit
				if firstChar == 95: #underscore
					line[MODULE_NAME] = "_u"
				elif firstChar >= 48 and firstChar <= 57:
					line[MODULE_NAME] = '_' + line[MODULE_NAME]
				elif not ((firstChar >= 65 and firstChar <= 90) or (firstChar >= 97 and firstChar <= 122)):
					line[MODULE_NAME] = '_s' + str(cnt)
					cnt = cnt + 1
				
				_NAME_MODULES.append(str.upper(line[MODULE_NAME]))
			except:
				_NAME_MODULES.append("")

			if line[2] == 0:			
				moduleSize = int(line[MODULE_WIDTH_ID]) * int(line[MODULE_HEIGHT_ID])
			else:
				moduleSize = int(line[MODULE_WIDTH_ID-2]) * int(line[MODULE_HEIGHT_ID-2])
				
			if (moduleSize > maxModuleSize):
				maxModuleSize = moduleSize
	
	return (maxModuleSize, modules, frames)

#--------------------------------------------------------------------
def writeInterface(fileName, modules, frames):
	fileName = os.path.split(fileName)[1]
	fileName = os.path.splitext(fileName)[0]
	
	fp.write("///////////////////////////////// "+str.upper(fileName)+"\n")
	fp.write("// ANIM //\n")
	
	#fp.write("interface ANIM_" + str.upper(fileName) + "\n")
	#fp.write("{\n")
	
	cnt =0 
	for name in _NAME_ANIMS:
		if name != "":
			fp.write("\t#define ANIM_"+ str.upper(fileName) + "_" + name + "\t %s\n" %cnt )
		cnt=cnt+1
	fp.write("\n" ) 

	fp.write("// FRAME //\n")
	#fp.write("interface FRAME_" + str.upper(fileName) + "\n")
	#fp.write("{\n")
	
	cnt =0 
	#print "a"
	for name in _NAME_FRAMES:
		if name != "":
			(width, height) = BuildConstantsTable(modules, frames[cnt])
			fp.write("\t#define FRAME_"+ str.upper(fileName) + "_"+ name + "\t %s\n" %cnt )
			#fp.write("\t#define FRAME_"+ str.upper(fileName) + "_"+ name + "_WIDTH\t %s\n"  %width  )
			#fp.write("\t#define FRAME_"+ str.upper(fileName) + "_"+ name + "_HEIGHT\t %s\n" %height )
		cnt=cnt+1
		
	fp.write("\n" ) 
	
	fp.write("// MODULE //\n")
	#fp.write("interface MODULE_" + str.upper(fileName) + "\n")
	#fp.write("{\n")
	
	cnt =0 

	for name in _NAME_MODULES:
		if name != "":
			fp.write("\t#define MODULE_"+ str.upper(fileName) + "_"+ name + "\t %s\n" %cnt )
		cnt=cnt+1
	fp.write("\n" ) 


#--------------------------------------------------------------------
# ########### #
# CODE START  #
# ########### #

if len(sys.argv) >= 2: # we have a single file to process
	fileName = sys.argv[1]

	targetFileName = fileName
	targetFileName = os.path.split(targetFileName)[1]
	targetFileName = os.path.splitext(targetFileName)[0]

#export .java
#fp = open("%s" % (targetFileName + '_anims.h'), "w")
fp = open("%s" % ('SPRITE_DESC.h'), "w")

if len(sys.argv) >= 2: # we have a single file to process
	processSprite(fileName)
	writeInterface(fileName)
else:
	maxModuleSize = 0
	
	fp.write("#ifndef _SPRITE_DESC_\n" )
	fp.write("#define _SPRITE_DESC_\n" )
	
	for f in glob.glob("*.sprite"):
		_NAME_ANIMS=[]
		_NAME_FRAMES=[]
		_NAME_MODULES=[]

		(maxModuleSize, modules, frames) = processSprite(f, maxModuleSize)
		writeInterface(f, modules, frames)
	

	
	for f in glob.glob("*\*.sprite"):
		_NAME_ANIMS=[]
		_NAME_FRAMES=[]
		_NAME_MODULES=[]

		(maxModuleSize, modules, frames) = processSprite(f, maxModuleSize)
		writeInterface(f, modules, frames)	

	#fp.write("interface ANIM_MODULES\n")
	#fp.write("{\n")
	#fp.write("\tfinal static int BIGGEST_MODULE = %s;\n" %maxModuleSize )
	#fp.write("};\n\n" ) 
	
	fp.write("#endif//_SPRITE_DESC_\n\n" ) 

# export end
fp.close()

