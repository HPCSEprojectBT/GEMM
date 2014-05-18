timing_full <- read.delim("./timing.out",check.names = FALSE, header=FALSE);
View(timing_full)
timing <- read.table("./timing.out",colClasses = c(rep("NULL", 2),rep("double", 10) ),check.names = FALSE, header=FALSE);
View(timing)
par(mar=c(4,7,2,1));
T1=apply(timing,1,mean)[1]
#boxplot(T1/t(timings_brutus_2),log  = "xy",main="strong scaling plot for n_samples=10.000.000",xlab="Number of threads used", ylab="speedup")
#abline(a=0, b=1, col="red")

plot(T1/apply(timing,1,mean),main="strong scaling plot for n_dofs = 1000",xlab="Number of threads used", ylab="speedup")
#plot(apply(timing,1,mean),main="strong scaling plot for n_samples=10.000.000",xlab="Number of threads used", ylab="speedup")
boxplot(t(timing), main="strong scaling plot for n_dofs = 1000",xlab="Number of threads used", ylab="time")
abline(a=0, b=1, col="red")
