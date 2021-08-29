#include "libex.h"

static void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_quick_sort(int array[], int left, int right)
{
	int	pivot;
	int	i;
	int	j;

	if (left >= right)
		return ;
	pivot = array[left];
	i = left;
	j = right;
	while (1)
	{
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i >= j)
			break ;
		swap(&array[i], &array[j]);
		i++;
		j--;
	}
	ft_quick_sort(array, left, i - 1);
	ft_quick_sort(array, j + 1, right);
}
