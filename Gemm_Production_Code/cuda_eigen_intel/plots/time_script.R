ssf <- read.csv("./timing_ss_fast_intel_cuda.csv", header=F)
#View(ssf)
ssf_t <- ssf[c(3,4,5,6,7,8,9,10,11,12)]
#View(ssf_t)
means_ssf=apply(ssf_t,1,mean)
boxplot(t(ssf_t), names = t(ssf[c(1)]),main="execution time fot n = 5040",xlab="Number of nodes", ylab="time in usecs")
#View(ssf[c(1)])
#View(means_ssf)
plot(t(ssf[c(1)]),means_ssf[1]/means_ssf,type="p",main="strong scaling plot (mpi-cuda, eigen) for n*n = 5040*5040", xlab="Number of nodes", ylab="speedup",col=1)
abline(a=0, b=1, col="red")

wsf <- read.csv("./timing_ws_fast_intel_cuda.csv", header=F)
View(wsf)
wsf_t <- wsf[c(3,4,5)]/100000
View(wsf_t)
means_wsf=apply(wsf_t,1,mean);
View(means_wsf)
#means_wsf=means_wsf/sqrt(wsf[c(1)]) #divide by number of cannon sends
View(means_wsf) #view after considering cannon sends
boxplot(t(wsf_t), names = t(wsf[c(1)]),main="execution time for dofs = 5040*540*n_nodes",xlab="Number of nodes", ylab="time in sec")
#abline(a=1, b=1, col="red")
length(t(means_wsf))
length(t(wsf[c(1)]))
plot(t(wsf[c(1)]),t(means_wsf[1]/means_wsf),type="p",main="weak scaling plot (mpi-cuda, eigen) for n = 5040*n_nodes", xlab="Number of nodes", ylab="speedup",col=1)

