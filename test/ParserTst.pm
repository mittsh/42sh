package ParserTst;

#
# To use this Class :
# use ParserTst;
# my $parse = ParserTst->new("pathname.tst");
# $parse->getCmd();	to get a command.
# $parse->getStdin();	to get a stdin.
# $parse->getStdout();	to get a stdout.
# $parse->getStderr();	to get a stderr.
# $parse->getRet();	to get a return value.
# $parse->getRef();	to get a reference command.
#


# --------------------------------------
sub new
{
    my ($class, $filepath) = @_;
    my $self = { };
    $self->{FileStr} = fileToStr($filepath);
    $self->{cmd} = getElement($self->{FileStr}, "cmd");
    $self->{stdout} = getElement($self->{FileStr}, "stdout");
    $self->{stdin} = getElement($self->{FileStr}, "stdin");
    $self->{stderr} = getElement($self->{FileStr}, "stderr");
    $self->{ret} = getElement($self->{FileStr}, "ret");
    $self->{ref} = getElement($self->{FileStr}, "ref");

    bless($self, $class);
    return ($self);
}

# --------------------------------------

sub getCmd
{
    my $self = shift;
    return $self->{cmd};
}
sub getStdout
{
    my $self = shift;
    return $self->{stdout};
}
sub getStdin
{
    my $self = shift;
    return $self->{stdin};
}
sub getStderr
{
    my $self = shift;
    return $self->{stderr};
}

sub getRet
{
    my $self = shift;
    return $self->{ret};
}

sub getRef
{
    my $self = shift;
    return $self->{ref};
}

# utils
# --------------------------------------
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

sub getElement
{
    my ($fileStr, $motif) = @_;
    my $str = "";

    if (!$fileStr){
	return (undef);
    }
    if ($fileStr =~ /<$motif>\n((.|\n)*)<\/$motif>/){
	$str =  $1;
    }

    return $str;
}

1;
