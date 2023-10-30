#include "ruby.h"
#include <unistd.h>
#include <linux/ptrace.h>
#include <sys/user.h> 
 
VALUE RegInfo = Qnil;
void Init_reginfo();
 
VALUE method_getr(VALUE self,VALUE arg,VALUE pid);
 
void Init_reginfo()
{
        RegInfo = rb_define_module("RegInfo");
        rb_define_method(RegInfo, "getr", method_getr,2 );
}
 
VALUE method_getr(VALUE self, VALUE arg, VALUE pid)
{
    char* input=RSTRING_PTR(arg);
    pid_t  process = NUM2INT(pid);
    struct user_regs_struct registers;
    long out=0;
    char outreg[10];
    ptrace(PTRACE_ATTACH,process,0,0); //attach to process
    waitpid(process,NULL,0);
    ptrace(PTRACE_GETREGS,process,&registers,&registers); //get'em
    if (!strncasecmp(input,"eax",3)){out = registers.eax;}  //make sure we don't cmpr case
    else if (!strncasecmp(input,"edx",3)){out = registers.edx;}
    else if (!strncasecmp(input,"ebx",3)){out = registers.ebx;}
    else if (!strncasecmp(input,"ecx",3)){out = registers.ecx;}
    else if (!strncasecmp(input,"ebp",3)){out = registers.ebp;}
    else if (!strncasecmp(input,"esi",3)){out = registers.esi;}
    else if (!strncasecmp(input,"eip",3)){out = registers.eip;}
    else {out =  registers.eip;} //default
    ptrace(PTRACE_DETACH,process,0,0); //detach from process
    snprintf(outreg,10,"%lx",out);
    return rb_str_new2(outreg);
}

/* 
  
Next it's straight forward, we create an extconf.rb file which when we execute generates the Makefile which will compile our module.

require 'mkmf'
extension_name = 'reginfo'
dir_config(extension_name)
create_makefile(extension_name)
And an example
require 'reginfo'
include  RegInfo 
	pid = fork do
	system("tail -f txt")
	end

 
puts getr("eip",pid) #here we get EIP

The above  prints something like b7f577d8


*/
