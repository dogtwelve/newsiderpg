def delCmdLine(fileName):
    file = open(fileName,"r");
    lines = file.readlines();
    file.close();
    out = "";
    for line in lines:
        pos = line.find("CommandLine");
        if(pos!=-1):#has CommandLine
            pos2 = line.find("wrunt.exe");
            if(pos2>pos):#wrunt.exe post with CommandLine
                line = "\t\t\t\tCommandLine=\"\"\n";
                #import re;
                #line = re.sub(r'CommandLine="([a-z]|[A-Z]|\b|&|\:|=|/|\\|.)*"',"CommandLine=\"\"",line);
        out += line;
    file = open(fileName,"w");
    file.write(out);
    file.close();
    
    
if __name__=="__main__":
    delCmdLine("tmp.vcproj");
