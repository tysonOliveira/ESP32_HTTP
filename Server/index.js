const express = require('express');

const app = express();

app.use(express.json());

let teste;

app.get('/dados', (req, res) => {
  res.status(200).send(`Temperatura: ${teste}`);
  console.log("Solicitação bem sucedida!")
})

app.post('/', (req, res) => {
  teste = req.body.dados;
  res.status(200).send(req.body.dados);
  console.log("Temperatura:", req.body.dados);
})

app.listen('3000', () => { console.log('Server is running') });