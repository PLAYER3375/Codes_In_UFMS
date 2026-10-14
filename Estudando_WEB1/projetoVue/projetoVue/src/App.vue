<script setup>
  import { ref, onMounted } from 'vue'

  const eventos = ref([])

  const API_URL = 'http://localhost:3000/eventos'

  //GET
  async function carregarEventos() {
    try {
      const resposta = await fetch(API_URL)
      eventos.value = await resposta.json()
    } catch (erro) {
      console.error('Erro ao buscar eventos:', erro)
    }
  }

  //gatilho do get
  onMounted(() => {
    carregarEventos()
  })
  
</script>

<template>
  <div class="menu">
    <!-- Indicador de carregamento -->
    <p v-if="carregando">Carregando eventos...</p>

    <!-- Exibição dos dados -->
    <ul v-else>
      <li v-for="evento in eventos" :key="evento.id">
        <strong>{{ evento.titulo }}</strong> - {{ evento.data }} ({{ evento.local }})
      </li>
    </ul>
  </div>
</template>

<style scoped>

  body{
    margin: 0;
    padding: 0;
    box-sizing: border-box;
  }

  .menu{
    display: flex;
    background-color: gray;
    border: 2px solid;
    border-radius: 10px;
  }

  .menu li{
    list-style: none;
  }

</style>
