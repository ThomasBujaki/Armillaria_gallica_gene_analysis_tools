args <- commandArgs(TRUE)
a <- args[1]
b <- args[2]
c <- as.numeric(args[3])
d <- as.numeric(args[4])
directory <- getwd()
library(ggplot2)

file_name <- paste0(directory, "/", a)
table <- read.table(file = file_name)

location <- table[[4]]
read_depth <- table[[10]]

data = data.frame(location, read_depth)

plot_name <- ggplot(data,aes(x=location, y = read_depth))+ 
	geom_line() +
	geom_vline(xintercept = c, color = "red") +
	geom_vline(xintercept = d, color = "red") +
	ggtitle(paste0(b, " locations: ", c, "-", d))


ggsave(filename = paste0(a,"_read_depth.pdf"), plot = plot_name)



