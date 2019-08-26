args <- commandArgs(TRUE)
a <- args[1]
directory <- getwd()
library(ggplot2)
library(reshape2)


file_name <- paste0(directory, "/scaffold",a,".Ar109_DP_locations" )

  
table <- read.table(file = file_name)
  
position <- table[[1]]
indel <- table[[2]]
read <- table[[3]]

data = data.frame(indel, read)

length_vs_count <- ggplot(data,aes(x = indel, y = read))+
  geom_line() +
  xlab("Indel") +
  ylab("Raw Read Depth") 


ggsave(filename = paste0(a,"_DP_locations.pdf"), plot = length_vs_count)



