args <- commandArgs(TRUE)
a <- args[1]
b <- args[2]
#c <- as.numeric(args[3])
#d <- as.numeric(args[4])
directory <- getwd()
library(ggplot2)

file_name <- paste0(directory, "/", a)
table <- read.table(file = file_name)

read_depth <- table[[3]]

data = data.frame(read_depth)

plot_name <- ggplot(data,aes(x = read_depth))+ 
	geom_histogram(binwidth = 5) +
	ggtitle(paste0(b))
ggsave(filename = paste0(a,"_read_depth_histogram.pdf"), plot = plot_name)
