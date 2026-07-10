# :globe_with_meridians: Um XSS um tanto quanto estranho

---

# Um XSS um tanto quanto estranho

Oi amigos, tudo certo com vocês? Hoje vim fazer meu primeiro writeup pra contar como eu fiz parar explorar em XSS de uma forma um pouco diferente, então vamos lá.

Para uma breve introdução, meu “nome hacker” é gato (pois eu quero provar que a curiosidade só fortalece o gato :D), tenho 19 anos, amo tecnologia e comecei recentemente na área de segurança da informação.

Então vamos lá!

Como o bug não foi arrumado, por questões éticas, irei chamar o site de redacted.xxx.br!

## Parte 1: A procura

Tudo começou com uma simples vontade de achar um bug em algum site e fazer um dinheirinho extra, a situação não tá fácil no Brasil… Então estava eu navegando na web, até que cai em um site .xxx.br, e como eu sei que os sites governamentais possuem um histórico muito ruim de segurança, pensei em dar uma olhada por cima da aplicação e ver se eu encontrava algo. Comecei injetando malwares nos inputs mais simples, porém tudo parecia muito bem sanitizado, então resolvi pegar um pouco mais pesado.

## Parte 2: As ferramentas

Parti para a enumeração de subdomínios utilizando a ferramenta [Sublist3r](https://github.com/aboul3la/Sublist3r), porém nada de estranho, então fui para o [ParamSpider](https://github.com/devanshbatham/ParamSpider) para analisar os parâmetros dos hosts encontrados. A lista ficou enorme, ainda mais que eu fui buscar tanto os gosta com retorno 200, quanto os com 404 (sempre bom ver se algo reflete em páginas 404 mal construídas).

Como eu ainda não tinha tentado automatizar o processo, fui abrindo todos os links da lista pra ver se tinha refletido ou não (você pode usar a ferramenta [Httpx](https://github.com/projectdiscovery/httpx), que com o parâmetros -match-string e -match-regex, você pode buscar a sua reflexão), até que encontrei a seguinte página:

Como você pode ver, apesar do parâmetro estar todo minúsculo, ele foi refletido de forma que a primeira letra era maiúscula, e o resto minúsculo, uma tratamento simples para nomes próprios,!

## Get gato the wizard’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Tentei injetar um payload para ver se o mesmo seria executado, porém o comportamento foi aplicado no meu alert(1), e o método não foi executado.

## Parte 3: A injeção

Como eu estava sem paciência, fiz o que todo sript kiddie faria, comecei a dar *Ctrl + C* e *Ctrl + V *em todos os payload que eu achei na internet. Se deu certo? É claro que não hahahhaha.

Como vi que nada estava dando certo, resolvi dar um tempo para a minha cabeça, fui tomar um água, respirar um pouco, e fiquei pensando sobre XSS de modo geral. Foi aí que por acaso lembrei de quando eu era menor e estava aprendendo a jogar xadrez, o professor montava desafios, onde as peças eram colocadas de uma certa maneira no tabuleiro, e em uma determinada quantidade de movimentos eu tinha que dar xeque mate (ganhar o jogo). Então voltei para o computador, e com a mentalidade dos desafios de xadrez, eu comecei a ver o XSS da mesma forma, cada movimento que eu faço, a aplicação pode se defender de alguma maneira, se o meu movimento não surtir um efeito positivo, eu desfaço ele e começo outra vez.

Comecei pesquisando algumas formas de realizar injeção de HTML, pois a princípio era o que estava funcionando. Até que cheguei na tabela de [HTML Charset](https://www.w3schools.com/html/html_charset.asp), que utilizando o valor numérico do caractere, precedido de ‘&’ e ‘#’ , é possível exibir em tela o caractere.

*Os caracteres & e # estão encodados em URL (%26 e %23 respectivamente) para que não sejam tratados como símbolos de construção de URL*

Na hora em que cliquei enter e vi que meu caractere não tinha sido alterado para maiúsculo eu já abri um sorriso de todo o tamanho.

Finalizando os testes, acabei com o seguinte payload: *<img%20src=x%20onerror=”%26%2397%26%23108%26%23101%26%23114%26%23116(1)”>. Em que o alert, está sendo enviado como HTML encoding.*

As minhas dicas para você são:

- Ferramentas são ótimas, mas é o jeito que você usa elas que as tornam ótimas!

- Tenha paciência, se preciso saia do computador por um tempo, jogue alguma coisa, e depois volte com a cabeça limpa!

- Stay curious!

E é isso! Espero que tenham gostado!

[Buy Me a Coffee!](https://www.buymeacoffee.com/gatothehacker)

---
