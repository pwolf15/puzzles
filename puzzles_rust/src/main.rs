
fn count_segments(s: String) -> i32 {
    let mut split = s.split_whitespace();
    let mut segments = 0;
 
    while split.next() != None
    {
        segments += 1;
    }

    return segments;
}

fn num_steps(num: i32) -> i32 {

    let mut rem = num;
    let mut num_steps = 0;

    while rem != 0
    {
        num_steps += 1;
        if rem % 2 == 0
        {
            rem /= 2;
        }
        else 
        {
            rem -= 1;
        }
    }

    return num_steps;
}

fn main() {
    println!("Hello, world!");
    println!("{}", count_segments("Hello, world!".to_string()));
    println!("{}", count_segments("welcome to the jungle".to_string()));
    println!("{}", count_segments("".to_string()));
    println!("{}", count_segments("hello".to_string()));
    println!("{}", num_steps(14));
}
