#!/usr/bin/perl
use warnings;
use strict;

my $string;
my $y;
my $x;
my $z;
my $num = 1;
my $width = 0.1;
my @colors = (
  "1.0f, 0.0f, 0.0f",
  "0.0f, 1.0f, 0.0f",
  "0.0f, 0.0f, 1.0f"
);
my $colorindex = 0;
my $howmany = ((1.0) / $width);

$string .= sprintf("#define FLOORSIZE %d\n", $howmany * $howmany * 4);
$string .= sprintf("float v[%s][24] = {\n", $howmany * $howmany * 4);

$z = 0;
for(my $r = 1.0; $r >= 0.0; $r--) {
  for(my $t = -1.0; $t <= 0.0; $t++) {
    $y = $r;
    for(my $i = 0; $i < $howmany; $i++) {
      $x = $t;
      for(my $n = 0; $n < $howmany; $n++) {
        my $color = $colors[$colorindex];
        $string .= sprintf("  {\n", $num);

        my $new_x;
        $new_x = $x + $width;

        my $new_y;
        $new_y = $y - $width;

        # Bottom left
        $string .= sprintf("    %.1ff, %.1ff, %.1ff, %s,\n", $x, $new_y, $z, $color);
        # Bottom right
        $string .= sprintf("    %.1ff, %.1ff, %.1ff, %s,\n", $new_x, $new_y, $z, $color);
        # Top left
        $string .= sprintf("    %.1ff, %.1ff, %.1ff, %s,\n", $x, $y, $z, $color);
        # Top right
        $string .= sprintf("    %.1ff, %.1ff, %.1ff, %s\n", $new_x, $y, $z, $color);

        $x += $width;

        $string .= "  },\n";
        $num++;
        if($colorindex < 2) {
          $colorindex++;
          $z = 0;
        } else {
          $colorindex = 0;
          $z = -1;
        }
      }
      $y -= $width;
    }
  }
}
$string .= "};\n";
print $string;
