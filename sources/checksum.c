#include <malloc.h>

void checksum(void *addr, size_t size, unsigned char *checksum)
{
	size_t		i;
	int		j;
	unsigned int	sum1;
	unsigned int	sum2;

	if (!addr)
		return ;
	i = 0;
	j = 0;
	sum1 = 0;
	sum2 = 0;
	while (i < size)
	{
		sum1 += *(unsigned char*)(addr + i);
		sum2 += *(unsigned char*)(addr + i) * ++j;
		++i;
	}
	checksum[0] = sum1 & 0xFF;
	checksum[1] = sum2 & 0xFF;
	//#ifndef DEBUG
		//ft_printf("sum1:%x\tsum2:%x\nsum1 & 0xFF:%x\tsum2 & 0xFF:%x\n",sum1, sum2, sum1 & 0xFF, sum2 & 0xFF);
		//sleep (4);
	//#endif
}

int	verif_checksum(void *addr, size_t size)
{
	unsigned char chkm[2];

	if (!addr)
		return (0);
	checksum(addr, size, chkm);
	//ft_printf("DEBUG in verif_checksum => addr:%x\tchkm[0]:%x\n\t\t\taddr+1:%x\tchkm[1]%x\n", *(unsigned char*)(addr + size), chkm[0],*(unsigned char*)(addr + size + 1), chkm[1]); 
	if (*(unsigned char*)(addr + size) == chkm[0] &&
		*(unsigned char*)(addr + size + 1) == chkm[1])
		return (1);
	return (0);
}