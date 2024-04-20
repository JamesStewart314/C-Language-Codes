/* This was my first code written independently in C. My knowledge of the language at the time was quite limited, so I ask that you disregard the bad practices involved in developing this code. */ 

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include "math_custom.h"

/*Loops Utilizados: final, loop1, loop2, Loop3, Loop4, Loop5, Loop6, Loop7, Loop8, Loop9, Loop10, Loop11, Loop12*/


double resultado=0;
void apresent();

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "Portuguese");

	char per, arm;
	int oper;
	double val1, val2, resultado_temp=0;

	apresent();

	while(scanf("%d", &oper) != EOF) {
			fflush(stdin);
			switch(oper) {
				case 1:
					system("cls");
					loop1:
					puts("\t\t//--------------SOMA---------------\\\\\n\t\t\\\\----PRESSIONE 'B' PARA VOLTAR----//\n");
					puts("Deseja utilizar o resultado acumulado na próxima operação? [s/n]\n");
					per = getch();
					switch(per) {
						case 'n':
							puts("Informe a Primeira Parcela da Soma: ");
							scanf("%lf", &val1);
							fflush(stdin);
							puts("Informe a Segunda Parcela da Soma: ");
							scanf("%lf", &val2);
							fflush(stdin);
							resultado_temp = soma(val1, val2);
							loop2:
							printf("\nRESULTADO:\t%lf\n\n", resultado_temp);
							puts("Deseja armazenar o resultado? [s/n]\n");
							arm = getch();
							switch(arm) {
								case 's':
									puts("Resultado Salvo!!! Pressione qualquer tecla para prosseguir.");
									getch();
									resultado = resultado_temp;
									break;
								case 'n':
									break;
								default:
									puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
									getch();
									system("cls");
									goto loop2;
									break;
							}
							break;

						case 's':
							puts("Informe a segunda parcela da soma:");
							scanf("%lf", &val1);
							fflush(stdin);
							resultado_temp = soma(val1, resultado);
							loop3:
							printf("\nRESULTADO:\t%lf\n\n", resultado_temp);
							puts("Deseja armazenar o resultado? [s/n]");
							arm = getch();
							switch(arm) {
								case 's':
									puts("Resultado Salvo!!! Pressione qualquer tecla para prosseguir.");
									getch();
									resultado = resultado_temp;
									break;
								case 'n':
									puts("Resultado descartado!!! Pressione qualquer tecla para prosseguir.");
									getch();
									break;
								default:
									puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
									getch();
									system("cls");
									goto loop3;
									break;
							}
							break;
						case 'b':
							goto final;
							break;
						default:
							puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
							getch();
							system("cls");
							goto loop1;
							break;
					}
					break;

				case 2:
					system("cls");
					Loop4:
					puts("\t\t//--------------SUBTRAÇÃO--------------\\\\\n\t\t\\\\------PRESSIONE 'B' PARA VOLTAR------//\n");
					puts("Deseja utilizar o resultado acumulado na próxima operação? [s/n]\n");
					per = getch();
					switch(per) {
						case 'n':
							puts("Informe o Minuendo da Subtração: ");
							scanf("%lf", &val1);
							fflush(stdin);
							puts("Informe o Subtraendo da Subtração: ");
							scanf("%lf", &val2);
							fflush(stdin);
							resultado_temp = subtr(val1, val2);
							Loop5:
							printf("\nRESULTADO:\t%lf\n\n", resultado_temp);
							puts("Deseja armazenar o resultado? [s/n]\n");
							arm = getch();
							switch(arm) {
								case 's':
									puts("Resultado Salvo!!! Pressione qualquer tecla para prosseguir.");
									getch();
									resultado = resultado_temp;
									break;
								case 'n':
									break;
								default:
									puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
									getch();
									system("cls");
									goto Loop5;
									break;
							}
							break;

						case 's':
							puts("Informe o Subtraendo da Subtração:");
							scanf("%lf", &val1);
							fflush(stdin);
							resultado_temp = subtr(val1, resultado);
							Loop6:
							printf("\nRESULTADO:\t%lf\n\n", resultado_temp);
							puts("Deseja Armazenar o Resultado? [s/n]");
							arm = getch();
							switch(arm) {
								case 's':
									puts("Resultado Salvo!!! Pressione Qualquer Tecla para Prosseguir.");
									getch();
									resultado = resultado_temp;
									break;
								case 'n':
									puts("Resultado descartado!!! Pressione Qualquer Tecla para Prosseguir.");
									getch();
									break;
								default:
									puts("Opção Inválida!!! Pressione Qualquer Tecla para Prosseguir.");
									getch();
									system("cls");
									goto Loop6;
									break;
							}
							break;
						case 'b':
							goto final;
							break;
						default:
							puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
							getch();
							system("cls");
							goto Loop4;
							break;
					}
					break;
				case 3:
                    system("cls");
					Loop7:
					puts("\t\t//--------------MULTIPLICAÇÃO--------------\\\\\n\t\t\\\\--------PRESSIONE 'B' PARA VOLTAR--------//\n");
					puts("Deseja utilizar o resultado acumulado na próxima operação? [s/n]\n");
					per = getch();
					switch(per) {
						case 'n':
							puts("Informe o Primeiro Fator do Produto: ");
							scanf("%lf", &val1);
							fflush(stdin);
							puts("Informe o Segundo Fator do Produto: ");
							scanf("%lf", &val2);
							fflush(stdin);
							resultado_temp = mult(val1, val2);
							Loop8:
							printf("\nRESULTADO:\t%lf\n\n", resultado_temp);
							puts("Deseja armazenar o resultado? [s/n]\n");
							arm = getch();
							switch(arm) {
								case 's':
									puts("Resultado Salvo!!! Pressione qualquer tecla para prosseguir.");
									getch();
									resultado = resultado_temp;
									break;
								case 'n':
									break;
								default:
									puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
									getch();
									system("cls");
									goto Loop8;
									break;
							}
							break;

						case 's':
							puts("Informe o segundo fator da multiplicação: ");
							scanf("%lf", &val1);
							fflush(stdin);
							resultado_temp = mult(val1, resultado);
							Loop9:
							printf("\nRESULTADO:\t%lf\n\n", resultado_temp);
							puts("Deseja armazenar o resultado? [s/n]");
							arm = getch();
							switch(arm) {
								case 's':
									puts("Resultado Salvo!!! Pressione qualquer tecla para prosseguir.");
									getch();
									resultado = resultado_temp;
									break;
								case 'n':
									puts("Resultado descartado!!! Pressione qualquer tecla para prosseguir.");
									getch();
									break;
								default:
									puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
									getch();
									system("cls");
									goto Loop9;
									break;
							}
							break;
						case 'b':
							goto final;
							break;
						default:
							puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
							getch();
							system("cls");
							goto Loop7;
							break;
					}
					break;
				case 4:
                    system("cls");
					Loop10:
					puts("\t\t//--------------DIVISÃO--------------\\\\\n\t\t\\\\-----PRESSIONE 'B' PARA VOLTAR-----//\n");
					puts("Deseja Utilizar o Resultado Acumulado na Próxima Operação? [s/n]\n");
					per = getch();
					switch(per) {
						case 'n':
							puts("Informe o Dividendo da Divisão: ");
							scanf("%lf", &val1);
							fflush(stdin);
							puts("Informe o Divisor da Divisão: ");
							scanf("%lf", &val2);
							fflush(stdin);
							if(val1 == 0 && val2 == 0) {
                                system("cls");
                                puts("!!! ERRO !!!\nO Resultado '0/0' é uma Indeterminação Matemática.");
                                puts("Pressione qualquer tecla para prosseguir.");
                                getch();
                                system("cls");
                                goto Loop10;
							}
							else {
                                if(val2 == 0) {
                                    system("cls");
                                    puts("!!! ERRO !!!\nTentativa de Divisão por Zero.");
                                    puts("Pressione qualquer tecla para prosseguir.");
									getch();
                                    system("cls");
                                    goto Loop10;
                                }
							}
							resultado_temp = divis(val1, val2);
							Loop11:
							printf("\nRESULTADO:\t%lf\n\n", resultado_temp);
							puts("Deseja armazenar o resultado? [s/n]\n");
							arm = getch();
							switch(arm) {
								case 's':
									puts("Resultado Salvo!!! Pressione qualquer tecla para prosseguir.");
									getch();
									resultado = resultado_temp;
									break;
								case 'n':
									break;
								default:
									puts("Opção Inválida!!! Pressione qualquer tecla para prosseguir.");
									getch();
									system("cls");
									goto Loop11;
									break;
							}
							break;

						case 's':
							puts("Informe o Divisor da Divisão: ");
							scanf("%lf", &val1);
							fflush(stdin);
							if(val1 == 0 && resultado_temp == 0) {
                                system("cls");
                                puts("!!! ERRO !!!\nO Resultado '0/0' é uma Indeterminação Matemática.");
                                puts("Pressione qualquer tecla para prosseguir.");
                                getch();
                                system("cls");
                                goto Loop10;
							}
							else {
                                if(val1 == 0) {
                                    system("cls");
                                    puts("!!! ERRO !!!\nTentativa de Divisão por Zero.");
                                    puts("Pressione qualquer tecla para prosseguir.");
									getch();
                                    system("cls");
                                    goto Loop10;
                                }
							}
							resultado_temp = divis(resultado, val1);
							Loop12:
							printf("\nRESULTADO:\t%lf\n\n", resultado_temp);
							puts("Deseja armazenar o resultado? [s/n]\n");
							arm = getch();
							switch(arm) {
								case 's':
									puts("Resultado Salvo!!! Pressione qualquer tecla para prosseguir.");
									getch();
									resultado = resultado_temp;
									break;
								case 'n':
									puts("Resultado descartado!!! Pressione qualquer tecla para prosseguir.");
									getch();
									break;
								default:
									puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
									getch();
									system("cls");
									goto Loop12;
									break;
							}
							break;
						case 'b':
							goto final;
							break;
						default:
							puts("Opção Inválida! Pressione qualquer tecla para prosseguir.");
							getch();
							system("cls");
							goto Loop10;
							break;
					}
					break;
				case 5:
					resultado = 0;
					break;
				default:
					system("cls");
					puts("!!! ERRO !!!");
					puts("Entrada inválida, selecione uma das opções disponíveis no menu.");
					getch();
					break;
			}
		final:
        oper = 0;
		system("cls");
		apresent();
	}
	puts("\n\033[32mObrigado por utilizar meu primeiro protótipo de Calculadora em linguagem C !!!\033[0m");
	getch();
	puts("\n\033[33mAss.:\033[0m \033[33mAllber Fellype\033[0m\n");
	getch();

	return 0;
}


void apresent() {
	puts("/----------------------C A L C U L A D O R A----------------------\\\n");
	puts("\tDigite 1 + ENTER para Somar;");
	puts("\tDigite 2 + ENTER para Subtrair;");
	puts("\tDigite 3 + ENTER para Multiplicar;");
	puts("\tDigite 4 + ENTER para Dividir;");
	puts("\tDigite 5 + ENTER para Limpar o Resultado Acumulado");
	puts("\tDigite CTRL + Z e ENTER para encerrar as operações !");
	printf("\n\n  RESULTADO ATUAL ACUMULADO:\t%lf\n", resultado);
	puts("\\-----------------------------------------------------------------/");
	printf("\n>>>>\t");
}
