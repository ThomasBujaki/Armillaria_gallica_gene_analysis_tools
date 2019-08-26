args <- commandArgs(TRUE)
a <- args[1]
directory <- getwd()
library(ggplot2)
file_name <- paste0(directory, "/", a)
table <- read.table(file = file_name)

scaffold <- table[[2]]
count <- table[[4]]
avg_depth <- table[[9]]

cumulat_avg = 0;
total_count = 0;
M1 = 0
M2 = 0
N = 0
for (i in 1:319){
	M1 = (cumulat_avg*total_count)
	M2 = (as.numeric(count[i])*as.numeric(avg_depth[i]))
	N = (as.numeric(total_count) + as.numeric(count[i]))
	cumulat_avg = (M1+M2)/N 
	total_count = N
}
print(cumulat_avg)
print(total_count)
x_axis <- c(seq(1, 319))
data = data.frame(scaffold, avg_depth, x_axis, count)
#print(data)


cont_vs_scaff_num <- ggplot(data,aes(x=x_axis, y = count))+ 
	geom_point() +
	xlab("Scaffold Number") +
	ylab("Number of sites with reads") +
	labs(title = unlist(strsplit(a, split='_', fixed=TRUE))[3])

avg_depth_vs_scaf_num <- ggplot(data,aes(x=x_axis, y = avg_depth))+ 
	geom_point() +
	xlab("Scaffold Number") +
	ylab("Average Read Depth") +
	labs(title = unlist(strsplit(a, split='_', fixed=TRUE))[3])

ggsave(filename = paste0(a,"_read_depth.pdf"), plot = avg_depth_vs_scaf_num)
ggsave(filename = paste0(a,"_count.pdf"), plot = cont_vs_scaff_num)



