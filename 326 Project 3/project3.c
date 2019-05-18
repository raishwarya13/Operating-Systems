//these inlcude files have to be included in anything we create
//these header files are need for ubuntu to find the files
#include <linux/module.h>      
#include <linux/kernel.h>      
#include <linux/sched.h>
// the signal had to be included because my ubuntu didnt like it
#include <linux/sched/signal.h>        
#include <linux/mm.h>
#include <linux/mm_types.h>
//this whole function finds the process in the memory and returns its property
void process(void){
struct task_struct* list1;
struct mm_struct* memory_manger_list;
struct vm_area_struct* virtural_machine_list;
size_t madeinto = 0;
//this is the addreass that we are tyring to find which can be any number
unsigned long p = 46483378;
//this for loop sereches for all process in the list
for_each_process(list1){
//this takes the memory mangement from the list1
memory_manger_list = (list1->mm);
//this checks to see if there any virtuial structures
if(memory_manger_list == NULL){
pr_info("Null\n");}
else{ virtural_machine_list = (memory_manger_list->mmap);//this takes the virtual machine structure from memory mangement
//this while loop keeps going in the virtual machine structure
while(virtural_machine_list != NULL){
//this makes sure thatthe address is inbetween the start to the end
if((virtural_machine_list->vm_start <= p) & (virtural_machine_list->vm_end >= p)){pr_info("Found Address -> [%lu]", p);
pr_info("start -> [%lu] end -> [%lu]\n", virtural_machine_list->vm_start, virtural_machine_list->vm_end);
//this makes sure that the adreass is to write, read or exec
//this checks to see if its writeable
(virtural_machine_list->vm_flags & (VM_WRITE))?pr_info("Write\n"):pr_info("not Write\n");
//this checks to see if its readable
(virtural_machine_list->vm_flags & (VM_READ))?pr_info("Read\n"):pr_info("not Read\n");
//this checks to see if its exectuable
(virtural_machine_list->vm_flags & (VM_EXEC))?pr_info("Exec\n"):pr_info("not Exec\n");
madeinto = 1;
//ths is when the address is found then the loop stops and doesnt run anymore
//Address is found so the loop can stop
goto STOP;}
//this makes it so that it goes to the next virtual machine list 
virtural_machine_list = (virtural_machine_list->vm_next);}}}
STOP:if(madeinto == 0) pr_info("The Address is Not Found");}
//this function starts the code
int init_module(void)
{printk(KERN_INFO "[ INIT ==\n");
process();
return 0;}
//this removes the code
void cleanup_module(void)
{printk(KERN_INFO "== CLEANUP ]\n");}
MODULE_LICENSE("lol");
