use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() -> io::Result<()> {
    let path = Path::new("output.txt");
    let file = File::open(&path)?;
    let reader = io::BufReader::new(file);
    let mut number: f64 = 0.0;
    for line in reader.lines() {
        let line = line?;
        if line.contains("Best objective") {
            let parts: Vec<&str> = line.split_whitespace().collect();
            if let Some(&current_number) = parts.last() {
                if current_number.parse::<f64>().unwrap_or(0.0) < number { // The </> should be switched if the value is supposed to be more or less depending on the OF.c
                    number = current_number.parse::<f64>().unwrap_or(0.0);
                }
            }
        }
    }
    println!("Best fitness is from all of the run throughs is: {number}");
    Ok(())
}