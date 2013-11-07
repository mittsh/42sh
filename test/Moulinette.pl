#! /usr/bin/perl

# This is us Moulinet
# There are many options for use this
# -a (default)
# -f
# -n
# -c
# -e

use ParserTst;
use strict;
use warnings;

my $NAME = "42SH (version 0.5)";
my $BLEU = "\033[34;1;4m";
my $UNDEF = "\033[37;1m";
my $VERT = "\033[32;1m";
my $ROUGE = "\033[31;1m";
my $ENDCOLOR = "\033[0m";
my $TOTAL_T = 0;

open(ECRIRE, ">html/index.html")
    or die ("Erreur de la creation du fichier html");

sub fileToStr
{
    my ($path) = @_;
    my $str = "";

    if (!(-e $path)) {
        print "Le fichier $path n'existe pas\n";
        return (undef);
    }
    open FD, $path;
    my @lines = <FD>;

    foreach my $l (@lines) {
        $str .= $l;
    }

    close FD;
    return ($str);
}

sub test
{
    my ($f, $param1) = @_;
    my $parse = ParserTst->new($f);
    my $ref_ret = undef;
    my $ref_stdout = undef;
    my $ref_stderr = undef;
    my $com_ret = undef;
    my $com_stdout = undef;
    my $com_stderr = undef;
    my $result_ret = undef;
    my $result_stdout = undef;
    my $result_stderr = undef;
    my $diff_stdout = undef;
    my $diff_stderr = undef;

    open (IN, ">", "stdin");
    print IN ($parse->getStdin());
    close(IN);


    if (!($parse->getRef() eq "")) {
        $ref_ret =
            system("cat stdin 2> /dev/null | ".$parse->getRef().
                   " > ref_stdout 2> ref_stderr");
        $ref_stdout = fileToStr("ref_stdout");
        $ref_stderr = fileToStr("ref_stderr");
    }
    else {
        $ref_ret = $parse->getRet();
        $ref_stdout = $parse->getStdout();
        $ref_stderr = $parse->getStderr();
    }

    $com_ret = system("cat stdin 2> /dev/null | ".$parse->getCmd().
                      " > com_stdout 2> com_stderr");
    $com_stdout = fileToStr("com_stdout");
    $com_stderr = fileToStr("com_stderr");

    $result_ret = ($com_ret eq $ref_ret);
    $result_stdout = ($com_stdout eq $ref_stdout);
    $result_stderr = ($com_stderr eq $ref_stderr);

    if ((!($param1 eq "-c")) && (!($param1 eq "--categories")) &&
        (!($param1 eq "-f")) && (!($param1 eq "--final")))
    {
        if (($result_ret eq 1)&&($result_stdout eq 1)&&($result_stderr eq 1)){
            print ECRIRE ('<div id="'.$f.'"> Test '.$f.':
<span style="color:#009900;"><strong>OK</strong></span></div>');
            print("Test ".$f.":\t ret=".$result_ret." stdout=".$result_stdout.
                  " stderr=".$result_stderr."\n");
        }else{
            system("diff com_stdout ref_stdout > diff_stdout");
            system("diff com_stderr ref_stderr > diff_stderr");

            $diff_stdout = fileToStr("diff_stdout");
            $diff_stderr = fileToStr("diff_stderr");

            print ECRIRE ('<div id="'.$f.'" class=b_t> Test '.$f.":
ERREUR"."");
            print ECRIRE ('<input type="button" id="voir'.$f.'"
            value="afficher l\'erreur"
            onClick="divaffiche(\''.$f.'Err\',\'voir'.$f.'\', \'cache'.$f.'\')"
            style="display:inline; margin-left:30px;"/>');
            print ECRIRE ('<input type="button" id="cache'.$f.'"
            value="cacher l\'erreur"
            onClick="divcache(\''.$f.'Err\',\'voir'.$f.'\', \'cache'.$f.'\')"
            style="display:none; margin-left:30px;"/> </div>');
            print ECRIRE ('<div id="'.$f.'Err" style="display:none;
             background-color:orange;">
                       <div><strong>Check return value : '
                          .$result_ret.
                          '</strong></div><div><strong>Standard output : '
                          .$result_stdout.
                          '</strong></div><div style="text-align:center;">
<textarea style="width:80%; height:150px;">'.$diff_stdout.
                          '</textarea></div>
                       <div><strong>Standard error : '.$result_stderr.
                          '</strong></div>
                       <div style="text-align:center;">
<textarea style="width:80%; height:150px;">'
                          .$diff_stderr.'</textarea></div>
             </div>');
            print("Test ".$f.":\t ret=".$result_ret." stdout=".$result_stdout.
                  " stderr=".$result_stderr."\n");

            print STDERR ("Diff STDOUT:\n");
            print STDERR $diff_stdout;

            print STDERR ("Diff STDERR:\n");
            print STDERR $diff_stderr;

            system("rm -f diff_stdout diff_stderr");
        }
    }

    system("rm -f ref_stderr ref_stdout");
    system("rm -f com_stdout com_stderr stdin");

    return ($result_ret && $result_stdout && $result_stderr);
}

sub category
{
    my ($dir, $param1) = @_;
    my $dir_42sh = undef;

    if  (!($param1 eq "-f") && !($param1 eq "--final"))
    {
        print ECRIRE ('<div id="'.$dir.'" class="header_group"><strong>Category
        </strong><em>'.$dir."</em></div>");
        $dir_42sh = $UNDEF."\n".$dir."\n".$ENDCOLOR;
        print($dir_42sh);
        print ECRIRE ('<div class="footer_group">');
    }
    my $total = 0;
    my $pourcentage = 0;
    my $success = 0;
    my $res = undef;
    my $print_42sh = undef;

    foreach my $f (glob($dir."*.tst")) {
        if (test($f, $param1)) {
            $success += 1;
        }
        $total += 1;
    }

    if  (($param1 eq "-n") or ($param1 eq "--number"))
    {
        if ($success == $total) {
            $res = "OK";
            print ECRIRE ("<div class=g_result>".$res."<br /><br /> "
                          .$success."/".$total." tests<br /></div>");
            $print_42sh = $VERT."\t\t\t\t".$res."\t ".$success."/".$total.
                " tests\n\n".$ENDCOLOR;
            print($print_42sh);
            $pourcentage = $success;
            $TOTAL_T = $TOTAL_T + $total;
        }
        else {
            $res = "KO";

            print ECRIRE ("<div class=b_result>".$res."<br /><br /> "
                          .$success."/".$total." tests<br /></div>");
            $print_42sh = $ROUGE."\t\t\t\t".$res."\t ".$success."/".$total.
                " tests\n\n".$ENDCOLOR;
            print($print_42sh);
            $pourcentage = $success;
            $TOTAL_T = $TOTAL_T + $total;
        }
    }

    if (!($param1 eq "-n") && !($param1 eq "--number"))
    {
        $pourcentage = $total == 0 ? 100 : (($success * 100) / $total);
    }

    if  (!($param1 eq "-f") && !($param1 eq "--final") && !($param1 eq "-n")
         && !($param1 eq "--number"))
    {
        if ($success == $total) {
            $res = "OK";
            if (($param1 eq "-c") or ($param1 eq "--categories") or
                ($param1 eq "-a") or ($param1 eq "--all") or ($param1 eq 0))
            {
                print ECRIRE ("<div class=g_result>".$res."<br /><br /> "
                              .$pourcentage."% des tests<br /></div>");

                print($VERT."\t\t\t\t".$res."\t ");
                printf("%.1f", $pourcentage);
                print("% des tests\n\n".$ENDCOLOR);
            }
            else
            {
#           print ECRIRE ("<div class=g_result>".$res."<br /><br /> ".$success."/".$total." tests<br /></div>");
#           $print_42sh = $VERT."\t\t\t\t".$res."\t ".$success."/".$total." tests\n\n".$ENDCOLOR;
#           print($print_42sh);
            }
        }
        else {
            $res = "KO";
            if (($param1 eq "-c") or ($param1 eq "--categories") or
                ($param1 eq "-a") or ($param1 eq "--all") or ($param1 eq 0))
            {
                print ECRIRE ("<div class=b_result>".$res."<br /><br /> ".
                              $pourcentage."% des tests<br /></div>");

                print($ROUGE."\t\t\t\t".$res."\t ");
                printf("%.1f", $pourcentage);
                print("% des tests\n\n".$ENDCOLOR);
            }
            else
            {
#       print ECRIRE ("<div class=b_result>".$res."<br /><br /> ".$success."/".$total." tests</div>");
#       $print_42sh = $ROUGE."\t\t\t\t".$res."\t ".$success."/".$total." tests\n\n".$ENDCOLOR;
#       print($print_42sh);
            }
        }
    }
    print ECRIRE ('</div>');
    return ($pourcentage);
}

sub header_html
{
    my $param1 = @_;
    my $title = undef;

    print ECRIRE ('<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr" >
  <head>
    <title> Moulinette '.$NAME.'!</title>
    <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
    <link rel="stylesheet" media="screen" type="text/css" title="Design"
href="design.css" />
    <script type="text/javascript"> <!--// [CDATA[
     function divaffiche(hide, voir, cache){
       document.getElementById(hide).style.display = "block";
       document.getElementById(cache).style.display = "inline";
       document.getElementById(voir).style.display = "none";
     }
     function divcache(hide, voir, cache){
       document.getElementById(hide).style.display = "none";
       document.getElementById(cache).style.display = "none";
       document.getElementById(voir).style.display = "inline";
     } // ]] --> </script>
  </head>
  <body>');

    print ECRIRE ('<div class="title"><h1> Moulinette'.$NAME.'</h1></div>');
    print ECRIRE ('<div class="toc">');
    $title = $BLEU."\n\t *** Moulinette".$NAME." ***\n\n".$ENDCOLOR;
    print($title);
    foreach my $d (glob("*/")) {
        print ECRIRE ('<ul>');
        if (!($d eq "build/") && !($d eq "html/") && !($d eq "main_test/")) {
            print ECRIRE ('<li class="category"><a href="#'.$d.'">
<img class="icon_chap" src="../'.$d.'img.png"/><b>'.$d.'</b></a></li>');
            if ($param1 eq 0)
            {
                print ECRIRE ('<li><ul>');
                foreach my $f (glob($d."*.tst")) {
                    print ECRIRE ('<li><a href="#'.$f.'">'.$f.'</a></li>');
                }
                print ECRIRE ('</li></ul>');
            }
        }
        print ECRIRE ('</ul>')
    }
    print ECRIRE ('</div><div class="content">');
}

sub footer_html()
{
    print ECRIRE ('</div></body></html>');
}

sub main
{
    my $lenght = @ARGV;
    my $param1 = 0;
    my $i = 0;
    my $total = 0;
    my $compt = 0;

    if ($lenght > 1)
    {
        if (($param1 eq "-e") or ($param1 eq "--select"))
        {

        }
    }
    elsif ($lenght eq 1)
    {
        $param1 = shift @ARGV;
        if (($param1 eq "-c") or ($param1 eq "--categories"))
        {
            header_html($param1);
            print($BLEU."\t\t Option : Categories\n\n".$ENDCOLOR);
            foreach my $d (glob("*/")) {
                if (!($d eq "build/") && !($d eq "html/") &&
                    !($d eq "main_test/")) {
                    $total = $total + category($d, $param1);
                    $compt = $compt + 1;
                }
            }

        }

        if (($param1 eq "-f") or ($param1 eq "--final"))
        {
            header_html($param1);
            print($BLEU."\t\t Option : Final\n\n".$ENDCOLOR);
            foreach my $d (glob("*/")) {
                if (!($d eq "build/") && !($d eq "html/") &&
                    !($d eq "main_test/")) {
                    $total = $total + category($d, $param1);
                    $compt = $compt + 1;
                }
            }
        }

        if (($param1 eq "-n") or ($param1 eq "--number"))
        {
            header_html();
            print("\t\t".$BLEU." Option : Number\n\n".$ENDCOLOR);
            foreach my $d (glob("*/")) {
                if (!($d eq "build/") && !($d eq "html/") &&
                    !($d eq "main_test/")) {
                    $total = $total + category($d, $param1);
                }
            }
            if ($total eq $TOTAL_T)
            {
                print("\n".$VERT."\t\t Total : ".$total.
                      "/".$TOTAL_T.$ENDCOLOR."\n\n");

            }
            else
            {
                print("\n".$ROUGE."\t\t Total : ".$total.
                      "/".$TOTAL_T.$ENDCOLOR."\n\n");
            }
        }

        if (($param1 eq "-a") or ($param1 eq "--all"))
        {
            header_html();
            print("\t\t".$BLEU." Option : All\n\n".$ENDCOLOR);
            foreach my $d (glob("*/")) {
                if (!($d eq "build/") && !($d eq "html/")
                    && !($d eq "main_test/")) {
                    $total = $total + category($d, $param1);
                    $compt = $compt + 1;
                }
            }
        }

        if (!($param1 eq "-n") && !($param1 eq "--number"))
        {
            if ($compt eq 0)
            {
                $compt = 1;
            }

            if ($total eq "100")
            {
                print('\t'.$VERT."\t\t Total : ");
                printf("%.1f", ($total/$compt));
                print("%\n\n".$ENDCOLOR);
            }
            else
            {
                print('\t'.$ROUGE."\t\t Total : ");
                printf("%.1f", ($total/$compt));
                print("%\n\n".$ENDCOLOR);
            }
        }
    }

    elsif ($lenght eq 0)
    {

        header_html();
        print("\t\t".$BLEU." Option : Default\n\n".$ENDCOLOR);
        foreach my $d (glob("*/")) {
            if (!($d eq "build/") && !($d eq "html/") &&
                !($d eq "main_test/")) {
                $total = $total + category($d, $param1);
                $compt = $compt + 1;
            }
        }
        if ($compt eq 0)
        {
            $compt = 1;
        }

        if ($total eq "100")
        {
            print("\t".$VERT."\t\t Total : ");
            printf("%.1f", ($total/$compt));
            print("%\n\n".$ENDCOLOR);

            print ECRIRE ("<div class=g_result><center><u> Total : ");
            print ECRIRE (($total / $compt)."%</u></center><br /></div>");
        }
        else
        {
            print("\t".$ROUGE."\t\t Total : ");
            printf("%.1f", ($total/$compt));
            print("%\n\n".$ENDCOLOR);

            print ECRIRE ("<div class=b_result><center><u> Total : ");
            print ECRIRE (($total / $compt)."%</u></center><br /></div>");
        }

    }

    print ECRIRE ("Result".$NAME."\n");
    footer_html();
}

main;

close(ECRIRE);
