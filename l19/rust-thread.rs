use std::time::Duration;

fn f(s: String) {
    println!("{}", s);
}

fn main() {
    let s = String::from("Hello world!");

    // start a thread
    let t = std::thread::spawn(move || {
        println!("Hello from thread!");
        f(s);
        std::thread::sleep(Duration::from_millis(5000));
    });

    // let y = s;
    // f(y);

    // wait for thread
    t.join().unwrap();
}
