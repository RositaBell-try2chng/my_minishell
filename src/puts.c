#include "minishell.h"

//Вывод символа
static void	ft_putchar(int c, int stdvar)
{
	write(stdvar, &c, 1);
}

//Вывод строки
void	ft_putstr(char *str)
{
	int	i;
	int	stdvar;

	stdvar = 1;
	if (str[0] == 'E' && str[1] == 'r' && str[2] == 'r'
		&& str[3] == 'o' && str[4] == 'r' && str[5] == '\n')
		stdvar = 2;
	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], stdvar);
		i++;
	}
}

//Вывод ошибок с выходом из программы
void	ft_puterror(t_shell *shell, int code)
{
	ft_putstr(COLOR_RED);
	ft_putstr("Error: ");
	if (code == 1)
		ft_putstr("Programmu neobhodimo zapuskat bez parametrov\n");
	if (code == 2)
		ft_putstr("Ne udalos videlit pamyat dlya struktury Shell\n");
	if (code == 3)
		ft_putstr("Ne udalos videlit pamyat dlya sohraneniya privetstviya\n");
	if (code == 4)
		ft_putstr("Ne udalos videlit pamyat dlya elementa lexera\n");
	if (code == 5)
		ft_putstr("Ne udalos videlit pamyat dlya znacheniya elementa lexera\n");
	if (code == 6)
		ft_putstr("Ne udalos videlit pamyat dlya funkcii miniglob\n");
	if (code == 7)
		ft_putstr("Ne udalos videlit pamyat dlya lexer-dereva\n");
	if (code == 8)
		ft_putstr("Ne udalos videlit pamyat dlya spiska uzlov lexer-dereva\n");
	if (code == 9)
		ft_putstr("Ne udalos videlit pamyat dlya struktury CMD\n");
	if (code == 10)
		ft_putstr("Ne udalos videlit pamyat dlya massiva cmd->argv\n");
	ft_putstr(COLOR_RESET);
	ms_shell_destroy(shell);
	exit(1);
}

//Вывод ошибок без выхода из программы
void	ft_puterror_noexit(t_shell *shell, int code)
{
	ft_putstr(COLOR_RED);
	ft_putstr("Error: ");
	if (code == 1)
		ft_putstr("Ne udalos voyti v ukazannuyu directoriyu\n");
	ft_putstr(COLOR_RESET);
	shell->output_error = 1;
}

//Вывод сообщения о выходе
void	ft_putexit(t_shell *shell)
{
	ft_putstr(COLOR_GREEN);
	if (OS_VERSION == 1)
		ft_putstr("Exit: Vi pokinuli programmu. Prihodite eshe!!!\n");
	if (OS_VERSION == 2)
		ft_putstr("\nExit: Vi pokinuli programmu. Prihodite eshe!!!\n");
	ft_putstr(COLOR_RESET);
	ms_shell_destroy(shell);
	exit(0);
}
