use std::cmp::Reverse;
use std::collections::{HashSet, BinaryHeap};
use std::iter::FromIterator;

fn solve(orders: Vec<Vec<u8>>, forbidden: Vec<Vec<u8>>, p: usize) -> usize {
    let forbidden: HashSet<Vec<u8>> = HashSet::from_iter(forbidden.into_iter());
    let mut zeros = vec![0; p];
    let mut ones = vec![0; p];
    for ord in orders {
        for i in 0..p {
            if ord[i] == 0 {
                zeros[i] += 1;
            } else {
                ones[i] += 1;
            }
        }
    }
    let mut start = vec![0; p];
    let mut complaints = 0;
    for i in 0..p {
        if zeros[i] > ones[i] {
            start[i] = 0;
            complaints += ones[i];
        } else {
            start[i] = 1;
            complaints += zeros[i];
        }
    }
    let mut seen = HashSet::new();
    let mut h = BinaryHeap::new();
    seen.insert(start.clone());
    let node = (Reverse(complaints), start);
    h.push(node);
    while let Some((complaints, order)) = h.pop() {
        if !forbidden.contains(&order) {
            return complaints.0;
        }
        for i in 0..p {
            let mut child_order = order.clone();
            let mut child_complaints = complaints.0;
            if order[i] == 0 {
                child_order[i] = 1;
                child_complaints += zeros[i];
                child_complaints -= ones[i];
            } else {
                child_order[i] = 0;
                child_complaints += ones[i];
                child_complaints -= zeros[i];
            }
            if !seen.contains(&child_order) {
                seen.insert(child_order.clone());
                h.push(
                    (Reverse(child_complaints), child_order)
                )
            }
        }
    }
    unreachable!()
}

fn main() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let t: usize = sc.read();
    for case_num in 1..=t {
        let (n, m, p): (usize, usize, usize) = (sc.read(), sc.read(), sc.read());
        let mut orders = vec![];
        for _ in 0..n {
            orders.push(
                sc.binary_vec()
            );
        }
        let mut forbidden = vec![];
        for _ in 0..m {
            forbidden.push(
                sc.binary_vec()
            );
        }
        let complaints = solve(orders, forbidden, p);
        sc.write(
            format!("Case #{}: {}", case_num, complaints)
        );
        sc.write("\n");
    }
}

pub struct IO<R, W: std::io::Write>(R, std::io::BufWriter<W>);

impl<R: std::io::Read, W: std::io::Write> IO<R, W> {
    pub fn new(r: R, w: W) -> IO<R, W> {
        IO(r, std::io::BufWriter::new(w))
    }
    pub fn write<S: ToString>(&mut self, s: S) {
        use std::io::Write;
        self.1.write_all(s.to_string().as_bytes()).unwrap();
    }
    pub fn read<T: std::str::FromStr>(&mut self) -> T {
        use std::io::Read;
        let buf = self
            .0
            .by_ref()
            .bytes()
            .map(|b| b.unwrap())
            .skip_while(|&b| b == b' ' || b == b'\n' || b == b'\r' || b == b'\t')
            .take_while(|&b| b != b' ' && b != b'\n' && b != b'\r' && b != b'\t')
            .collect::<Vec<_>>();
        unsafe { std::str::from_utf8_unchecked(&buf) }
            .parse()
            .ok()
            .expect("Parse error.")
    }
    pub fn usize0(&mut self) -> usize {
        self.read::<usize>() - 1
    }
    pub fn vec<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        (0..n).map(|_| self.read()).collect()
    }
    pub fn chars(&mut self) -> Vec<char> {
        self.read::<String>().chars().collect()
    }

    pub fn binary_vec(&mut self) -> Vec<u8> {
        self.read::<String>()
            .bytes()
            .map(|b| b - b'0')
            .collect()
    }
}