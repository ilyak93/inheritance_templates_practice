import sys

def main():
    if len(sys.argv) <= 1:
        print "Usage: %s [input_file]" % sys.argv[0]
        return
    sep = '.'
    file_name = sys.argv[1].split(sep, 1)[0] + ".c"
    
    with open(sys.argv[1]) as f:
        with open(file_name, 'w') as o:
            o.write("void test() {\n")
            o.write("   int studentId;\n")
            o.write("   int* students;\n")
            o.write("   int size;\n")
            for line_num, line in enumerate(f):
                line = line.split()
                if line[0] == "Init":
                    o.write("   void* DS = Init();")
                elif line[0] == "AddStudent":
                    o.write("   AddStudent(DS,%s,%s,%s);" % (line[1], line[2], line[3]))
                elif line[0] == "AddTeam":
                    o.write("   AddTeam(DS,%s);" % line[1])
                elif line[0] == "MoveStudentToTeam":
                    o.write("   MoveStudentToTeam(DS,%s,%s);" % (line[1], line[2]))
                elif line[0] == "GetMostPowerful":
                    o.write("   GetMostPowerful(DS,%s,&studentId);" % line[1])
                elif line[0] == "RemoveStudent":
                    o.write("   RemoveStudent(DS,%s);" % line[1])
                elif line[0] == "GetAllStudentsByPower":
                    o.write("   GetAllStudentsByPower(DS,%s,&students, &size);\n" % line[1])
                    o.write("   free(students);\n")
                    o.write("   students=NULL;")
                elif line[0] == "IncreaseLevel":
                    o.write("   IncreaseLevel(DS,%s,%s);" % (line[1], line[2]))
                else:
                    o.write("   Quit(&DS);")
                o.write(" // %s\n" % (line_num+1))
            o.write("}\n")


main()

